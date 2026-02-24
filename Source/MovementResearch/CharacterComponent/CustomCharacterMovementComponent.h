// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ObjectMacros.h"
#include "CustomCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_Climbing	UMETA(DisplayName = "Climbing"),
	CMOVE_MAX		UMETA(Hidden),
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOVEMENTRESEARCH_API UCustomCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
private:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
    	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	void SweepAndStoreWallHits();
	
	//Collision params to wall detect
	UPROPERTY(category = "Character Movement: Climbing", EditAnywhere)
	int CollisionCapsuleRadius = 50;
	
	UPROPERTY(category = "Character Movement: Climbing", EditAnywhere)
	int CollisionCapsuleHalfHeight = 72;
	
	TArray<FHitResult> CurrentWallHits;
	
	FCollisionQueryParams ClimbQueryParams;
	
	//Params to decide can char climbing
	UPROPERTY(category = "Character Movement: Climbing", EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "75.0"))
	float MinHorizontalDegreesToStartClimbing = 25.0f;
	
	bool CanStartClimbing();
	
	//Params to check wall height
	bool EyeHeightTrace(const float TraceDistant) const;
	
	bool IsFacingSurface(const float Steepness) const;
	
	//Update move
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
	
	bool bWantsToClimb = false;
protected:


public:
	
	// Sets default values for this component's properties
	UCustomCharacterMovementComponent();
	
	virtual void PhysWalking(float deltaTime, int32 Iterations) override;
	
	void TryClimbing();
	
	void CancelClimbing();
	
	bool IsClimbing() const;
	
	UFUNCTION(BlueprintPure)
	FVector GetClimbingSurfaceNormal() const;
};
