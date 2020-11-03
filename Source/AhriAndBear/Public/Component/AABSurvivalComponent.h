// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABSurvivalStats.h"
#include "GameBase/Define.h"
#include "AABSurvivalComponent.generated.h"

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UAABSurvivalComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAABSurvivalComponent();

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Survival")
	FABSurvivalStat Health;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Survival")
	FABSurvivalStat Warmth;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Survival")
	FABSurvivalStat Thirst;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Survival")
	FABSurvivalStat Hunger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival")
	float UpdateInterval = 2.0f;

	UFUNCTION()
	void UpdateStats(float deltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE FSurvivalData GetSurvivalData() const { return FSurvivalData{ Health.CurrentValue, Hunger.CurrentValue, Thirst.CurrentValue, Warmth.CurrentValue }; }
	void AddSurvivalData(const FSurvivalData& value);
};
