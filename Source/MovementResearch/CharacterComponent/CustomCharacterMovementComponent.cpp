// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"


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

	// ...
	
}


// Called every frame
void UCustomCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCustomCharacterMovementComponent::PhysWalking(float deltaTime, int32 Iterations)
{
	Super::PhysWalking(deltaTime, Iterations);
	
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, TEXT("Custom movement working"));
}

