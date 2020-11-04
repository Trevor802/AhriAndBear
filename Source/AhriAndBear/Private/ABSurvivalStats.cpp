// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSurvivalStats.h"

FABSurvivalStat::FABSurvivalStat() {
	StartingValue = MaxValue;
}

FORCEINLINE float UABSurvivalStatFunctions::GetStatPercentage(const FABSurvivalStat& stat) {
	return stat.CurrentValue / stat.MaxValue;
}

// For blueprint side
FORCEINLINE float UABSurvivalStatFunctions::GetCurrentValue(const FABSurvivalStat& stat) {
	return stat.CurrentValue;
}

void UABSurvivalStatFunctions::AddToCurrentValue(FABSurvivalStat& stat, float value)
{
	stat.CurrentValue = FMath::Clamp(stat.CurrentValue + value, 0.f, stat.MaxValue);
}

// For blueprint side
FORCEINLINE float UABSurvivalStatFunctions::GetMaxValue(const FABSurvivalStat& stat) {
	return stat.MaxValue;
}

// For blueprints
FORCEINLINE float UABSurvivalStatFunctions::SetRateOfChange(FABSurvivalStat& stat, float newRateOfChange) {
	stat.RateOfChange = newRateOfChange;
	return stat.RateOfChange;
}

FORCEINLINE void UABSurvivalStatFunctions::TickStat(FABSurvivalStat& stat, float deltaTime) {
	stat.CurrentValue += stat.RateOfChange * deltaTime;
}

FORCEINLINE void UABSurvivalStatFunctions::StartStat(FABSurvivalStat& stat) {
	stat.CurrentValue = stat.StartingValue;
}
