// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABAnimalCharacter.h"
#include "ABDogCharacter.generated.h"

/**
 * 
 */


UCLASS()
class AHRIANDBEAR_API AABDogCharacter : public AABAnimalCharacter
{
	GENERATED_BODY()

	void MoveToTargetActor(APawn* Pawn);
	
public:
	AABDogCharacter();

	UFUNCTION()
	void HandleSeePawn(APawn* Pawn);

	UFUNCTION()
	void HandleHearNoise(APawn* OtherActor, const FVector& Location, float Volume);

	virtual void UseAbility() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
