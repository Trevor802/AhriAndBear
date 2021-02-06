// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSurvivalStats.h"

FABSurvivalStat::FABSurvivalStat() {
	StartingValue = MaxValue;
}

float UABSurvivalStatFunctions::GetStatPercentage(const FABSurvivalStat& stat) {
	return stat.CurrentValue / stat.MaxValue;
}

bool UABSurvivalStatFunctions::IsStatZeroed(const FABSurvivalStat& stat) {
	return stat.CurrentValue <= 0;
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
	auto oldValue = stat.CurrentValue;
	stat.CurrentValue = FMath::Clamp(stat.CurrentValue + stat.RateOfChange * deltaTime, 0.f, stat.MaxValue);

	// Was okay, but now zero
	if (stat.CurrentValue == 0.f && oldValue > 0.f) {
		stat.OnStatZeroStateChanged.Broadcast(FStatZeroedStateChangedInfo(stat.StatName, oldValue, stat.CurrentValue));
	}
	// Was zero, but replenished
	else if (stat.CurrentValue > 0.f && oldValue <= 0.f) {
		stat.OnStatZeroStateChanged.Broadcast(FStatZeroedStateChangedInfo(stat.StatName, oldValue, stat.CurrentValue));
	}
}

void UABSurvivalStatFunctions::StartStat(FABSurvivalStat& stat, FString statName) {
	stat.CurrentValue = stat.StartingValue <= 0.0f ? stat.MaxValue : stat.StartingValue;
	stat.StatName = statName;
}
