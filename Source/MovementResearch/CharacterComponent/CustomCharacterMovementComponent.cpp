// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"
#include "DrawDebugHelpers.h"


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

