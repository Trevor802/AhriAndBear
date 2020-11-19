// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABSurvivalStats.h"
#include "GameBase/Define.h"
#include "AABSurvivalComponent.generated.h"

class IABStatModifierInterface;

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

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Survival")
	FABSurvivalStat Stamina;

	UPROPERTY(VisibleAnywhere, Category = "Character | Survival | Deprecated")
	float UpdateInterval = 2.0f;

	void UpdateStats(float deltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE FSurvivalData GetSurvivalData() const { return FSurvivalData{ Health.CurrentValue, Hunger.CurrentValue, Thirst.CurrentValue, Warmth.CurrentValue, Stamina.CurrentValue }; }
	void AddSurvivalData(const FSurvivalData& value);

	void AddModifier(IABStatModifierInterface* modifier);

	void RemoveModifier(IABStatModifierInterface* modifier);

private:

	void UpdateRateOfChange(FABSurvivalStat& stat, const float defaultRoC, float(IABStatModifierInterface::*statModMethod)(UAABSurvivalComponent*, float, float), bool (IABStatModifierInterface::*doesModMethod)(void) const);

	//UPROPERTY(VisibleAnywhere, Category = "Character | Survival | Modifiers")
	TArray<IABStatModifierInterface*> StatModifiers;
	UPROPERTY(VisibleAnywhere, Category = "Character | Survival")
	float defaultHungerRateOfChange;
	UPROPERTY(VisibleAnywhere, Category = "Character | Survival")
	float defaultThirstRateOfChange;
};
