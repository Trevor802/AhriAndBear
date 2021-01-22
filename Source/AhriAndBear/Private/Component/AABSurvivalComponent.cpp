// Fill out your copyright notice in the Description page of Project Settings.


#include "AABSurvivalComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "ABStatModifierInterface.h"

// Sets default values for this component's properties
UAABSurvivalComponent::UAABSurvivalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UAABSurvivalComponent::UpdateStats(float deltaTime)
{
	UABSurvivalStatFunctions::TickStat(Thirst, deltaTime);
	UABSurvivalStatFunctions::TickStat(Hunger, deltaTime);
	UABSurvivalStatFunctions::TickStat(Stamina, deltaTime);
}

// Called when the game starts
void UAABSurvivalComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UABSurvivalStatFunctions::StartStat(Thirst, "Thirst");
	UABSurvivalStatFunctions::StartStat(Hunger, "Hunger");
	UABSurvivalStatFunctions::StartStat(Stamina, "Stamina");

	// TODO: Do we want a separate one for each stat? We can have flags for if the
	// stat is zeroed or not and when both are set to true, it becomes true.
	// It's an interesting problem - we're not really keeping track of two animals,
	// but four statistics. If we added a third, that'd jump up to six and so forth.
	Thirst.OnStatZeroStateChanged.AddDynamic(this, &UAABSurvivalComponent::RespondToStatZeroedStateChange);
	Hunger.OnStatZeroStateChanged.AddDynamic(this, &UAABSurvivalComponent::RespondToStatZeroedStateChange);

	defaultHungerRateOfChange = Hunger.RateOfChange;
	defaultThirstRateOfChange = Thirst.RateOfChange;
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

void UAABSurvivalComponent::AddModifier(IABStatModifierInterface* modifier)
{
	StatModifiers.Add(modifier);
	StatModifiers.Sort();

	// Only update the corresponding stats if they modify that stat. Otherwise, we waste time.
	if (modifier->DoesModifyHungerRate()) {
		UpdateRateOfChange(Hunger, defaultHungerRateOfChange, &IABStatModifierInterface::GetHungerRateModifier, &IABStatModifierInterface::DoesModifyHungerRate);
	}
	if (modifier->DoesModifyThirstRate()) {
		UpdateRateOfChange(Thirst, defaultThirstRateOfChange, &IABStatModifierInterface::GetThirstRateModifier, &IABStatModifierInterface::DoesModifyThirstRate);
	}

	StatModifierAdded.Broadcast(FStatModifierChangedInfo(this, modifier));
}

void UAABSurvivalComponent::RemoveModifier(IABStatModifierInterface* modifier)
{
	StatModifiers.Remove(modifier);	
	StatModifiers.Sort();

	// Only update the corresponding stats if they modify that stat. Otherwise, we waste time.
	if (modifier->DoesModifyHungerRate()) {
		UpdateRateOfChange(Hunger, defaultHungerRateOfChange, &IABStatModifierInterface::GetHungerRateModifier, &IABStatModifierInterface::DoesModifyHungerRate);
	}
	if (modifier->DoesModifyThirstRate()) {
		UpdateRateOfChange(Thirst, defaultThirstRateOfChange, &IABStatModifierInterface::GetThirstRateModifier, &IABStatModifierInterface::DoesModifyThirstRate);
	}

	StatModifierRemoved.Broadcast(FStatModifierChangedInfo(this, modifier));
}

void UAABSurvivalComponent::UpdateRateOfChange(FABSurvivalStat& stat, const float defaultRoC, float(IABStatModifierInterface::*statModMethod)(UAABSurvivalComponent*, float, float), bool (IABStatModifierInterface::*doesModMethod)(void) const)
{
	float rateOfChange = defaultRoC;
	
	for (auto mod : StatModifiers) {
		if (mod == nullptr) continue;
		if ((mod->*doesModMethod)()) {
			rateOfChange = (mod->*statModMethod)(this, defaultRoC, rateOfChange);
		}
	}
	UABSurvivalStatFunctions::SetRateOfChange(stat, rateOfChange);
}

void UAABSurvivalComponent::RespondToStatZeroedStateChange(const FStatZeroedStateChangedInfo& stateChangeInfo) {
	// We need an event for when both stats have dropped below zero.
}
