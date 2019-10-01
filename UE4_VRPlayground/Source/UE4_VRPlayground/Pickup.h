// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class UE4_VRPLAYGROUND_API APickup : public AActor
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RepelForceBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RepelForceVariation;


private:

	bool bSimulatingPhysics;

public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
