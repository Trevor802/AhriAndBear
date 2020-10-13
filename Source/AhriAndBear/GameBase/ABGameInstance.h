// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Define.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) 
	void Clear();
	UFUNCTION(BlueprintCallable)
	bool Has(const EAnimalType animalType) const;
	UFUNCTION(BlueprintCallable)
	void Add(const EAnimalType animalType, const FAnimalData& animalData);
	UFUNCTION(BlueprintPure)
	FAnimalData Get(const EAnimalType animalType) const;
private:
	TMap<EAnimalType, FAnimalData> AnimalSurvivalData;
	
};
