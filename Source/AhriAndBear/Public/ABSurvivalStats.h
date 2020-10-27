// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ABSurvivalStats.generated.h"


USTRUCT(BlueprintType)
struct FABSurvivalStat {
	GENERATED_BODY()

	FABSurvivalStat();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival")
	float MaxValue = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival")
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Survival")
	float RateOfChange = -1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival")
	float StartingValue;
};

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API UABSurvivalStatFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Character | Survival")
	static float GetStatPercentage(const FABSurvivalStat& stat);

	static void TickStat(FABSurvivalStat& stat, float deltaTime);

	static void StartStat(FABSurvivalStat& stat);
};
