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

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cable")
	class UPhysicsConstraintComponent* ConstraintComponent;

	// Component that allow to do elements type cable
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cable")
	class UCableComponent* CableComponent;

protected:

	// Extra cable lenght needed to detect that the cable has been pulled
	UPROPERTY(EditDefaultsOnly, Category = "Cable")
	float MinPullLength = 25.0f;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cable")
	bool bIsPulling;

	// Gets the length of the cable
	UFUNCTION(BlueprintCallable, Category = "Cable")
	float GetCableLength();

	// BlueprintImplementableEvent called by C++, received by a Blueprint and allow to override
	UFUNCTION(BlueprintImplementableEvent, Category = "Cable")
	void OnPull();


	UPROPERTY(EditDefaultsOnly, Category = "Cable")
	TSubclassOf<APickup> PickupToSpawnClass;


public:

	virtual void Drop_Implementation(class UMotionControllerComponent *MotionController) override;

	virtual void Pickup_Implementation(class UMotionControllerComponent *MotionController) override;


private:

	float InitialCableLength;	
};
