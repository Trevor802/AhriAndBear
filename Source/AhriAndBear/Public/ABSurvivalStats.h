// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ABSurvivalStats.generated.h"

struct FABSurvivalStat;

DECLARE_DELEGATE_OneParam(FStatValueZeroed, FABSurvivalStat&);

USTRUCT(BlueprintType)
struct FABSurvivalStat {
	GENERATED_BODY()

	FABSurvivalStat();

	/**
	* The maximum value of a stat. This value should not be directly edited.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival")
	float MaxValue = 100.f;

	/**
	* The stat's current value. This should NOT be modified directly. (Oh to let
	* blueprints call struct functions so I can have protected/private variables...)
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival")
	float CurrentValue;

	/**
	* The amount that this stat will change by over time.
	*
	* Negative numbers will reduce the stat and positive numbers will replenish it.
	* During normal execution, this value should NOT be changed. If you want this
	* value to change dynamically, you should use the ABStatModifierInterface and
	* pipeline pattern. See ABRestArea and AABSurvivalComponent for examples.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Survival")
	float RateOfChange = -1.f;

	/**
	* This sets the current value of the stat when play begins.
	*
	* Make this value negative or zero to have CurrentValue set to MaxValue when play begins.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival")
	float StartingValue;

	/**
	* This delegate is triggered when CurrentValue equals zero.
	*/
	FStatValueZeroed OnStatZeroed;
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

	UFUNCTION(BlueprintCallable, Category = "Character | Survival")
		static void AddToCurrentValue(FABSurvivalStat& stat, float value);

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

	/**
	* Changes the stat's current value each frame.
	*
	* @param stat
	*   The stat that should be ticked.
	* @param deltaTime
	*   The amount of time that's elapsed since the last frame.
	*/
	static void TickStat(FABSurvivalStat& stat, float deltaTime);

	/**
	* Sets the stat to its initial value.
	*
	* This is called by the AABSurvival component in BeginPlay.
	*
	* @param stat
	*   The stat to initialize.
	*/
	static void StartStat(FABSurvivalStat& stat);
};
