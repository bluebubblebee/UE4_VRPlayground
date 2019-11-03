// Fill out your copyright notice in the Description page of Project Settings.


#include "Rope.h"

#include "CableComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ARope::ARope()
{
	PrimaryActorTick.bCanEverTick = true;

	CableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("CableComponent"));
	CableComponent->SetupAttachment(Root);

	ConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("ConstraintComponent"));
	ConstraintComponent->SetupAttachment(Root); 
}


void ARope::BeginPlay()
{
	Super::BeginPlay();

	InitialCableLength = GetCableLength();
}

void ARope::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bUsing) return;

	float CurrentCableLength = GetCableLength() - InitialCableLength;

	// Check if current cable length is more than the minimun
	if (!bIsPulling)
	{
		if (CurrentCableLength >= MinPullLength)
		{
			bIsPulling = true;

			// Call the event
			OnPull();

			Drop(CurrentMotionController);			
		}
	}
	
	
}

void ARope::Pickup_Implementation(class UMotionControllerComponent *MotionController)
{
	Super::Pickup_Implementation(MotionController);

	// Reset to default
	bIsPulling = false;

}

void ARope::Drop_Implementation(class UMotionControllerComponent *MotionController)
{
	Super::Drop_Implementation(MotionController);

	// Reset to default
	bIsPulling = false;
}

float ARope::GetCableLength()
{
	// Get component location in  World Space
	float lenght = FVector::Dist(ConstraintComponent->GetComponentLocation(), Base->GetComponentLocation());
	return lenght;
}