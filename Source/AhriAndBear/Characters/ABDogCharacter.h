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
	
public:
	AABDogCharacter();

	virtual void UseAbility() override;
};
