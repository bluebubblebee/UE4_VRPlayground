// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
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
	Base->SetCollisionProfileName(FName("NoCollision"));
	Base->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Base->SetupAttachment(Root);

	// Collider for the pickup
	InteractiveCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractiveCollider"));
	InteractiveCollider->SetupAttachment(Base);
	InteractiveCollider->SetCollisionProfileName(FName("Interactive"));

	PickSnapLocator = CreateDefaultSubobject<USceneComponent>(TEXT("PickSnapLocator"));
	PickSnapLocator->SetupAttachment(Base);


	// Forces
	RepelForceBase = 500000;
	RepelForceVariation = 200000;

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

