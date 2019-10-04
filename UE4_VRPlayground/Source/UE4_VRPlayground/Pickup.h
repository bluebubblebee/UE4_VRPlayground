// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PickupInterface.h"

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class UE4_VRPLAYGROUND_API APickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	class UBoxComponent* Base;

	// Collider for the object
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	UBoxComponent* InteractiveCollider;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	USceneComponent* PickSnapLocator;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	bool bUsing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RepelForceBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RepelForceVariation;


private:

	bool bSimulatingPhysics;

public:	
	// Sets default values for this actor's properties
	APickup();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

public:	

	/// PICKUP INTERFACE /////
	// This will be called by the motion controller when an object Pickup has been found
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup Interface")
	void Pickup(class UMotionControllerComponent *MotionController);

	virtual void Pickup_Implementation(class UMotionControllerComponent *MotionController) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup Interface")
	void Drop(class UMotionControllerComponent *MotionController);

	virtual void Drop_Implementation(class UMotionControllerComponent *MotionController) override;

	/// PICKUP INTERFACE /////

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	class UMotionControllerComponent *CurrentMotionController;

};
