// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Rope.generated.h"

/**
 * 
 */
UCLASS()
class UE4_VRPLAYGROUND_API ARope : public APickup
{
	GENERATED_BODY()

public:

	ARope();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cable")
	class UPhysicsConstraintComponent* ConstraintComponent;

	// Component that allow to do elements type cable
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cable")
	class UCableComponent* CableComponent;
	
};
