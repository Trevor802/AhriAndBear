// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSurvivalStats.h"

FABSurvivalStat::FABSurvivalStat() {
	StartingValue = MaxValue;
}

FORCEINLINE float UABSurvivalStatFunctions::GetStatPercentage(const FABSurvivalStat& stat) {
	return stat.CurrentValue / stat.MaxValue;
}

FORCEINLINE void UABSurvivalStatFunctions::TickStat(FABSurvivalStat& stat, float deltaTime) {
	stat.CurrentValue += stat.RateOfChange * deltaTime;
}

FORCEINLINE void UABSurvivalStatFunctions::StartStat(FABSurvivalStat& stat) {
	stat.CurrentValue = stat.StartingValue;
}
