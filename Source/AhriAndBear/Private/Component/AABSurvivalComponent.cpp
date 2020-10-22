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

	// ...
	StartingHealth = MaxHealth;
	StartingThirst = MaxThirst;
	StartingFullness = MaxFullness;
	StartingWarmth = MaxWarmth;
}


void UAABSurvivalComponent::UpdateStats(float deltaTime)
{
	TickStat(CurrentHealth, MaxHealth, HealthChangeRate, deltaTime);
	TickStat(CurrentThirst, MaxThirst, ThirstChangeRate, deltaTime);
	TickStat(CurrentFullness, MaxFullness, FullnessChangeRate, deltaTime);
	TickStat(CurrentWarmth, MaxWarmth, WarmthChangeRate, deltaTime);
}

// Called when the game starts
void UAABSurvivalComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHealth = StartingHealth;
	CurrentFullness = StartingFullness;
	CurrentThirst = StartingThirst;
	CurrentWarmth = StartingWarmth;
}


// Called every frame
void UAABSurvivalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStats(DeltaTime);
}

FORCEINLINE void UAABSurvivalComponent::TickStat(float& currentValue, int maxValue, float delta, float deltaTime)
{
	currentValue = FMath::Clamp<float>(currentValue + delta * deltaTime, 0, maxValue);
}

void UAABSurvivalComponent::AddSurvivalData(const FSurvivalData& value)
{
		
}

