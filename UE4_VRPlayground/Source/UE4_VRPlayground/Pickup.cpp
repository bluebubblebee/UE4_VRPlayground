// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "MotionControllerComponent.h"
#include "Components/BoxComponent.h"

APickup::APickup()
{
	// Create Components
	// Component Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Base
	Base = CreateDefaultSubobject<UBoxComponent>(TEXT("Base"));
	Base->SetSimulatePhysics(true);
	Base->SetBoxExtent(FVector(1, 1, 1));
	Base->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Base->SetupAttachment(Root);

	// Collider for the pickup
	InteractiveCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractiveCollider"));
	InteractiveCollider->SetupAttachment(Base);
	InteractiveCollider->SetCollisionProfileName(FName("Interactive"));

	bUsing = false;

	PrimaryActorTick.bCanEverTick = true;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	bSimulatingPhysics = Base->IsSimulatingPhysics();	
}


void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/// PICKUP INTERFACE /////
void APickup::Pickup_Implementation(UMotionControllerComponent *MotionController)
{

	if (!bUsing)
	{
		bUsing = true;
		// Helds a reference to the current motion controller
		CurrentMotionController = MotionController;

		// Attach to the Base Component
		Base->SetSimulatePhysics(false);
		Base->AttachToComponent(MotionController, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	}
}


void APickup::Drop_Implementation(UMotionControllerComponent *MotionController)
{ 

	if (MotionController == nullptr || MotionController == CurrentMotionController)
	{
		bUsing = false;
		// Detach to the Base Component
		Base->SetSimulatePhysics(bSimulatingPhysics);
		CurrentMotionController = nullptr;

		Base->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

/// PICKUP INTERFACE /////

