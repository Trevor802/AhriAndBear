// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSurvivalStats.h"

FABSurvivalStat::FABSurvivalStat() {
	StartingValue = MaxValue;
}

float UABSurvivalStatFunctions::GetStatPercentage(const FABSurvivalStat& stat) {
	return stat.CurrentValue / stat.MaxValue;
}

// For blueprint side
float UABSurvivalStatFunctions::GetCurrentValue(const FABSurvivalStat& stat) {
	return stat.CurrentValue;
}

void UABSurvivalStatFunctions::AddToCurrentValue(FABSurvivalStat& stat, float value)
{
	auto finalValue = FMath::Clamp(stat.CurrentValue + value, 0.f, stat.MaxValue);
	stat.CurrentValue = FMath::Clamp(stat.CurrentValue + value, 0.f, stat.MaxValue);
}

// For blueprint side
float UABSurvivalStatFunctions::GetMaxValue(const FABSurvivalStat& stat) {
	return stat.MaxValue;
}

// For blueprints
float UABSurvivalStatFunctions::SetRateOfChange(FABSurvivalStat& stat, float newRateOfChange) {
	stat.RateOfChange = newRateOfChange;
	return stat.RateOfChange;
}

void UABSurvivalStatFunctions::TickStat(FABSurvivalStat& stat, float deltaTime) {
	stat.CurrentValue = FMath::Clamp(stat.CurrentValue + stat.RateOfChange * deltaTime, 0.f, stat.MaxValue);
}

void UABSurvivalStatFunctions::StartStat(FABSurvivalStat& stat) {
	stat.CurrentValue = stat.StartingValue;
}
