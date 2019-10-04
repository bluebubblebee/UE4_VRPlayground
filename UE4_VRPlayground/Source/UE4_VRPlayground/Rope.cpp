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

	UE_LOG(LogTemp, Warning, TEXT("ARope::BeginPlay %f"), InitialCableLength);

	
}

void ARope::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bWaitToEndPulling)
	{
		waitTimeToEndPulling += DeltaTime;

		// Wait to seconds to drop and spawn something
		if (waitTimeToEndPulling >= 0.3f)
		{
			bWaitToEndPulling = false;
			waitTimeToEndPulling = 0.0f;

			UE_LOG(LogTemp, Warning, TEXT("OnEndPulling.ForceDrop %f "), waitTimeToEndPulling);

			// Spawn object
			if (PickupToSpawnClass != nullptr)
			{
				const FVector Location = GetActorLocation();

				UE_LOG(LogTemp, Warning, TEXT("Spawn Pickup %f, %f, %f "), Location.X, Location.Y, Location.Z);

				GetWorld()->SpawnActor<APickup>(PickupToSpawnClass, Location, FRotator(0, 0, 0));

			}


		}
	}


	if (!bUsing) return;

	float CurrentCableLength = GetCableLength() - InitialCableLength;

	//UE_LOG(LogTemp, Warning, TEXT("CurrentCableLenght: %f"), CurrentCableLength);

	// Check if current cable length is more than the minimun
	if (!bIsPulling)
	{
		if (CurrentCableLength >= MinPullLength)
		{
			UE_LOG(LogTemp, Warning, TEXT("On Pull(CurrentCableLength >= MinPullLength) %f"), CurrentCableLength);

			bIsPulling = true;

			// Delay release the cable
			bWaitToEndPulling = true;
			waitTimeToEndPulling = 0.0f;

			Drop(CurrentMotionController);			
		}
	}
	
	
}

void ARope::Pickup_Implementation(class UMotionControllerComponent *MotionController)
{
	Super::Pickup_Implementation(MotionController);

	// Reset to default
	bIsPulling = false;
	//bWaitToEndPulling = false;
}

void ARope::Drop_Implementation(class UMotionControllerComponent *MotionController)
{
	Super::Drop_Implementation(MotionController);

	// Reset to default
	bIsPulling = false;
	//bWaitToEndPulling = false;
}

float ARope::GetCableLength()
{
	// Get component location in  World Space

	float lenght = FVector::Dist(ConstraintComponent->GetComponentLocation(), Base->GetComponentLocation());

	//UE_LOG(LogTemp, Warning, TEXT("ARope::GetCableLength %f"), lenght);

	return lenght;
}