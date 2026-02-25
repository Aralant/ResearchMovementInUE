// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"


bool UCustomCharacterMovementComponent::CanStartClimbing()
{
	for (FHitResult& Hit : CurrentWallHits)
	{
		const FVector HorizontalNormal = Hit.Normal.GetSafeNormal2D();
		
		const float HorizontalDot = FVector::DotProduct(UpdatedComponent->GetForwardVector(), -HorizontalNormal);
		const float VerticalDot = FVector::DotProduct(Hit.Normal, HorizontalNormal);
		
		const float HorizontalDegrees = FMath::RadiansToDegrees(FMath::Acos(HorizontalDot));
		const bool bIsCeiling = FMath::IsNearlyZero(VerticalDot);
		
		if (HorizontalDegrees <= MinHorizontalDegreesToStartClimbing && !bIsCeiling && IsFacingSurface(VerticalDot))
		{
			return true;
		}
	}
	return false;
}

bool UCustomCharacterMovementComponent::EyeHeightTrace(const float TraceDistant) const
{
	FHitResult UpperEdgeHit;
	
	const FVector Start = UpdatedComponent->GetComponentLocation() +
		(UpdatedComponent->GetUpVector() * GetCharacterOwner()->BaseEyeHeight);
	const FVector End = Start + UpdatedComponent->GetForwardVector() *TraceDistant;
	
	return GetWorld()->LineTraceSingleByChannel(UpperEdgeHit, Start, End, ECC_WorldStatic, ClimbQueryParams);
}

//
bool UCustomCharacterMovementComponent::IsFacingSurface(const float Steepness) const
{
	constexpr float BaseLength = 80;
	const float SteepnessMultiplier = 1 + (1 - Steepness) * 5;

	return EyeHeightTrace(BaseLength * SteepnessMultiplier);
}

void UCustomCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,
	const FVector& OldVelocity)
{
	if (bWantsToClimb)
	{
		SetMovementMode(EMovementMode::MOVE_Custom, ECustomMovementMode::CMOVE_Climbing);
	}
	
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
}

void UCustomCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode,
	uint8 PreviousCustomMode)
{
	if (IsClimbing())
	{
		//off rotation to mouse because climb on wall
		bOrientRotationToMovement = false;
		
		UCapsuleComponent* Capsule = GetCharacterOwner()->GetCapsuleComponent();
		if (Capsule != nullptr)
		{
			Capsule->SetCapsuleHalfHeight(Capsule->GetUnscaledCapsuleHalfHeight() - ClimbingCollisionShrinkAmount);
		}
	}
	
	const bool bWasClimbing = PreviousMovementMode == MOVE_Custom && PreviousCustomMode == CMOVE_Climbing;
	if (bWasClimbing)
	{
		bOrientRotationToMovement = true;
		
		const FRotator StandRotation = FRotator(0, UpdatedComponent->GetComponentRotation().Yaw, 0);
		UpdatedComponent->SetRelativeRotation(StandRotation);
		
		UCapsuleComponent* Capsule = GetCharacterOwner()->GetCapsuleComponent();
		if (Capsule != nullptr)
		{
			Capsule->SetCapsuleHalfHeight(Capsule->GetUnscaledCapsuleHalfHeight() + ClimbingCollisionShrinkAmount, true);
		}
		
		//After stop climbing reset move
		StopMovementImmediately();
	}
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}

// Sets default values for this component's properties
UCustomCharacterMovementComponent::UCustomCharacterMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	ClimbQueryParams.AddIgnoredActor(GetOwner());
	
}


// Called every frame
void UCustomCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SweepAndStoreWallHits();
}

void UCustomCharacterMovementComponent::SweepAndStoreWallHits()
{
	const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CollisionCapsuleRadius, CollisionCapsuleHalfHeight);
	
	const FVector StartOffset = UpdatedComponent->GetForwardVector() * 20;
	
	
	//Start/End location for a Sweep, as it doesn't trigger hits on Landscapes.
	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
	const FVector End = Start + UpdatedComponent->GetForwardVector();
	
	TArray<FHitResult> Hits;
	const bool HitWall = GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity,
			ECC_WorldStatic, CollisionShape, ClimbQueryParams);
	
	if (HitWall)
	{
		CurrentWallHits = Hits;
		for (const FHitResult& Hit : Hits)
		{
			// contact point
			DrawDebugSphere(
				GetWorld(),
				Hit.ImpactPoint,
				8.f,
				12,
				FColor::Red,
				false,
				0.1f
			);

			// normal
			DrawDebugLine(
				GetWorld(),
				Hit.ImpactPoint,
				Hit.ImpactPoint + Hit.ImpactNormal * 40.f,
				FColor::Yellow,
				false,
				0.1f,
				0,
				2.f
			);
		}
	}
	else
	{
		CurrentWallHits.Reset();
	}

	
	DrawDebugCapsule(
		GetWorld(),
		Start,
		CollisionCapsuleHalfHeight,
		CollisionCapsuleRadius,
		FQuat::Identity,
		FColor::Blue,
		false,          // не навсегда
		0.03f           // время жизни (1 кадр)
	);

	DrawDebugCapsule(
		GetWorld(),
		End,
		CollisionCapsuleHalfHeight,
		CollisionCapsuleRadius,
		FQuat::Identity,
		FColor::Purple,
		false,
		0.03f
	);
	
	
}

void UCustomCharacterMovementComponent::PhysWalking(float deltaTime, int32 Iterations)
{
	Super::PhysWalking(deltaTime, Iterations);
	
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, TEXT("Custom movement working"));
}

void UCustomCharacterMovementComponent::TryClimbing()
{
	if (CanStartClimbing())
	{
		bWantsToClimb = true;
	}
}

void UCustomCharacterMovementComponent::CancelClimbing()
{
	bWantsToClimb = false;
}

bool UCustomCharacterMovementComponent::IsClimbing() const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::CMOVE_Climbing;
}

FVector UCustomCharacterMovementComponent::GetClimbingSurfaceNormal() const
{
	return CurrentWallHits.Num() > 0 ? CurrentWallHits[0].Normal : FVector::ZeroVector;
}

void UCustomCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	if (CustomMovementMode == ECustomMovementMode::CMOVE_Climbing)
	{
		PhysClimbing(deltaTime, Iterations);
	}
	Super::PhysCustom(deltaTime, Iterations);
}

void UCustomCharacterMovementComponent::PhysClimbing(float deltaTime, int32 Iterations)
{
}


