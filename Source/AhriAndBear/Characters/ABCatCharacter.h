// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABAnimalCharacter.h"
#include "ABCatCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABCatCharacter : public AABAnimalCharacter
{
	GENERATED_BODY()

	void MoveToTargetActor(APawn* Pawn);

public:
	UFUNCTION()
	void HandleSeePawn(APawn* Pawn);

	UFUNCTION()
	void HandleHearNoise(APawn* OtherActor, const FVector& Location, float Volume);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
