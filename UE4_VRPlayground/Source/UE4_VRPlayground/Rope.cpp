// Fill out your copyright notice in the Description page of Project Settings.


#include "Rope.h"

#include "CableComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ARope::ARope()
{
	PrimaryActorTick.bCanEverTick = true;

	CableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("CableComponent"));
	CableComponent->SetupAttachment(Root);

	ConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("ConstraintComponent"));
	ConstraintComponent->SetupAttachment(Root);
}