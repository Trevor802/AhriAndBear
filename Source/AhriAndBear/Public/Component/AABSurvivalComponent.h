// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABSurvivalStats.h"
#include "GameBase/Define.h"
#include "ABStatModifierInterface.h"
#include "AABSurvivalComponent.generated.h"

class UAABSurvivalComponent;
class AABAnimalCharacter;

/**
* Struct for the FStatModifiersChanged event.
*/
USTRUCT(Blueprintable, Category = "Character | Survival | Events")
struct FStatModifierChangedInfo {
	GENERATED_BODY()
public:
	FStatModifierChangedInfo() {}
	FStatModifierChangedInfo(UAABSurvivalComponent* sender, IABStatModifierInterface* modifier) : SurvivalComponent(sender) {
		StatModifier.SetInterface(modifier);
	}

	UPROPERTY(BlueprintReadonly, Category = "Character | Survival | Events")
	UAABSurvivalComponent* SurvivalComponent;
	UPROPERTY(BlueprintReadonly, Category = "Character | Survival | Events")
	TScriptInterface<IABStatModifierInterface> StatModifier;
};

/**
* Delegate for when a stat modifier is added or removed.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatModifiersChanged, const FStatModifierChangedInfo&, info);

/**
* Struct for the FAnimalCriticalConditionChanged event.
*/
USTRUCT(Blueprintable, Category = "Character | Survival | Events")
struct FAnimalCriticalConditionChangedInfo {
	GENERATED_BODY()
public:
	FAnimalCriticalConditionChangedInfo() {}
	FAnimalCriticalConditionChangedInfo(AABAnimalCharacter* animal, bool inCriticalCondition) :
		Owner(animal),
		IsNowInCriticalCondition(inCriticalCondition)
	{}

	UPROPERTY(BlueprintReadonly, Category = "Character | Survival | Events")
	AABAnimalCharacter* Owner;

	UPROPERTY(BlueprintReadonly, Category = "Character | Survival | Events")
		bool IsNowInCriticalCondition;
};

/**
* Delegate for when an animal enters or leaves critical condition.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAnimalCriticalConditionChanged, UAABSurvivalComponent*, sender, const FAnimalCriticalConditionChangedInfo&, info);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UAABSurvivalComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAABSurvivalComponent();

	UPROPERTY(VisibleAnywhere, Category = "Character | Survival | Deprecated")
	FABSurvivalStat Health;

	UPROPERTY(VisibleAnywhere, Category = "Character | Survival | Deprecated")
	FABSurvivalStat Warmth;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Survival")
	FABSurvivalStat Thirst;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Survival")
	FABSurvivalStat Hunger;

	UPROPERTY(VisibleAnywhere, Category = "Character | Survival | Deprecated")
	float UpdateInterval = 2.0f;

	void UpdateStats(float deltaTime);

	UPROPERTY(BlueprintAssignable, Category = "Character | Survival | Events")
	FStatModifiersChanged StatModifierAdded;

	UPROPERTY(BlueprintAssignable, Category = "Character | Survival | Events")
	FStatModifiersChanged StatModifierRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Character | Survival | Events")
	FAnimalCriticalConditionChanged OnCriticalConditionChanged;

	/**
	* Is the animal in critical condition?
	*
	* @return
	*   TRUE if both thirst and hunger are at zero or lower.
	*/
	UFUNCTION(BlueprintPure, Category = "Character | Survival")
	bool IsInCriticalCondition() const { return zeroedStats >= RequiredSurvivalStats; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE FSurvivalData GetSurvivalData() const { return FSurvivalData{ Health.CurrentValue, Hunger.CurrentValue, Thirst.CurrentValue, Warmth.CurrentValue }; }
	void AddSurvivalData(const FSurvivalData& value);

	void AddModifier(IABStatModifierInterface* modifier);

	void RemoveModifier(IABStatModifierInterface* modifier);

private:

	void UpdateRateOfChange(FABSurvivalStat& stat, const float defaultRoC, float(IABStatModifierInterface::*statModMethod)(UAABSurvivalComponent*, float, float), bool (IABStatModifierInterface::*doesModMethod)(void) const);

	/**
	* Responds to the OnStatZeroStateChanged events on Hunger and Thirst.
	*/
	UFUNCTION()
	void RespondToStatZeroedStateChange(const FStatZeroedStateChangedInfo& stateChangeInfo);
	
	TArray<IABStatModifierInterface*> StatModifiers;
	UPROPERTY(VisibleAnywhere, Category = "Character | Survival")
	float defaultHungerRateOfChange;
	UPROPERTY(VisibleAnywhere, Category = "Character | Survival")
	float defaultThirstRateOfChange;

	const int RequiredSurvivalStats = 2;

	int zeroedStats = 0;
};
