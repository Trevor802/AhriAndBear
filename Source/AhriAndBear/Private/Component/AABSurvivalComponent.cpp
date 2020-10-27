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
}

// Called when the game starts
void UAABSurvivalComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UABSurvivalStatFunctions::StartStat(Health);
	UABSurvivalStatFunctions::StartStat(Thirst);
	UABSurvivalStatFunctions::StartStat(Hunger);
	UABSurvivalStatFunctions::StartStat(Warmth);
}


// Called every frame
void UAABSurvivalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStats(DeltaTime);
}
