// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameBase/Define.h"
#include "AABSurvivalComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UAABSurvivalComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAABSurvivalComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival")
	float UpdateInterval = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Health")
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Survival | Health")
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Survival | Health")
	float HealthChangeRate = -1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Health")
	float StartingHealth;

	// Thirst-related stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Thirst")
	float MaxThirst = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Survival | Thirst")
	float CurrentThirst;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Survival | Thirst")
	float ThirstChangeRate = -1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Thirst")
	float StartingThirst;

	// Hunger-related stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Hunger")
	float MaxFullness = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Survival | Hunger")
	float CurrentFullness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Survival | Hunger")
	float FullnessChangeRate = -1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Hunger")
	float StartingFullness;

	// Warmth-related stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Warmth")
	float MaxWarmth = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Survival | Warmth")
	float CurrentWarmth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Survival | Warmth")
	float WarmthChangeRate = -1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Warmth")
	float StartingWarmth;

	UFUNCTION()
	void UpdateStats(float deltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Updates the specified stat.
	void TickStat(float& currentValue, int maxValue, float delta, float deltaTime);
	FORCEINLINE FSurvivalData GetSurvivalData() const { return FSurvivalData{ CurrentHealth, CurrentFullness, CurrentThirst, CurrentWarmth }; }
	void AddSurvivalData(const FSurvivalData& value);
};
