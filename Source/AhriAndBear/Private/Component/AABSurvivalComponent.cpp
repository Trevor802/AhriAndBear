// Fill out your copyright notice in the Description page of Project Settings.


#include "AABSurvivalComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UAABSurvivalComponent::UAABSurvivalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UAABSurvivalComponent::UpdateStats(float deltaTime)
{
	UABSurvivalStatFunctions::TickStat(Health, deltaTime);
	UABSurvivalStatFunctions::TickStat(Thirst, deltaTime);
	UABSurvivalStatFunctions::TickStat(Hunger, deltaTime);
	UABSurvivalStatFunctions::TickStat(Warmth, deltaTime);
	UABSurvivalStatFunctions::TickStat(Stamina, deltaTime);
}

// Called when the game starts
void UAABSurvivalComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UABSurvivalStatFunctions::StartStat(Health);
	UABSurvivalStatFunctions::StartStat(Thirst);
	UABSurvivalStatFunctions::StartStat(Hunger);
	UABSurvivalStatFunctions::StartStat(Warmth);
	UABSurvivalStatFunctions::StartStat(Stamina);
}


// Called every frame
void UAABSurvivalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStats(DeltaTime);
}

void UAABSurvivalComponent::AddSurvivalData(const FSurvivalData& value)
{
	UABSurvivalStatFunctions::AddToCurrentValue(Health, value.Health);
	UABSurvivalStatFunctions::AddToCurrentValue(Warmth, value.Warmth);
	UABSurvivalStatFunctions::AddToCurrentValue(Thirst, value.Thirst);
	UABSurvivalStatFunctions::AddToCurrentValue(Hunger, value.Hunger);
	UABSurvivalStatFunctions::AddToCurrentValue(Stamina, value.Stamina);
}
