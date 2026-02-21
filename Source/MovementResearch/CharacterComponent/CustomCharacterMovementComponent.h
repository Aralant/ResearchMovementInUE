// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomCharacterMovementComponent.generated.h"


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
	
	UPROPERTY(category = "Character Movement: Climbing", EditAnywhere)
	int CollisionCapsuleRadius = 50;
	
	UPROPERTY(category = "Character Movement: Climbing", EditAnywhere)
	int CollisionCapsuleHalfHeight = 72;
	
	TArray<FHitResult> CurrentWallHits;
	
	FCollisionQueryParams ClimbQueryParams;
protected:


public:
	
	// Sets default values for this component's properties
	UCustomCharacterMovementComponent();
	


	
	virtual void PhysWalking(float deltaTime, int32 Iterations) override;
};
