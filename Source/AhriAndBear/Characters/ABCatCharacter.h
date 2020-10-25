// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABAnimalCharacter.h"
#include "ABCatCharacter.generated.h"

class UPostProcessComponent;

UCLASS()
class AHRIANDBEAR_API AABCatCharacter : public AABAnimalCharacter
{
	GENERATED_BODY()

public:
	AABCatCharacter();
	virtual void UseAbility() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPostProcessComponent* postProcess;
	bool abilityOn;

	void AbilityEnd();
};
