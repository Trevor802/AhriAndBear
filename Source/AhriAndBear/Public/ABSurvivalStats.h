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
 * Provides functions that can be used on SurvivalStats.
 */
UCLASS()
class AHRIANDBEAR_API UABSurvivalStatFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	* Gets the current value of the stat as a percentage (current value / max value).
	* 
	* @param stat
	*   The stat to query.
	* @return
	*   The amount of the stat remaining as a percentage.
	*/
	UFUNCTION(BlueprintPure, Category = "Character | Survival")
	static float GetStatPercentage(const FABSurvivalStat& stat);

	/**
	* Gets the current value of the given stat.
	*
	* @param stat
	*   The stat to check.
	* @return
	*   The stat's current value.
	*/
	UFUNCTION(BlueprintPure, Category = "Character | Survival")
		static float GetCurrentValue(const FABSurvivalStat& stat);

	/**
	* Gets the max value of the given stat.
	* 
	* @param stat
	*   The stat to check.
	* @return
	*   The stat's max value.
	*/
	UFUNCTION(BlueprintPure, Category = "Character | Survival")
		static float GetMaxValue(const FABSurvivalStat& stat);

	/**
	* Sets the rate of change for this stat.
	* 
	* @param stat
	*   The stat whose rate of change should be modified.
	* @param newRateOfChange
	*   The new rate of change.
	* @return
	*   The new rate of change.
	*/
	UFUNCTION(BlueprintCallable, Category = "Character | Survival")
		static float SetRateOfChange(FABSurvivalStat& stat, float newRateOfChange);

	static void TickStat(FABSurvivalStat& stat, float deltaTime);

	static void StartStat(FABSurvivalStat& stat);
};
