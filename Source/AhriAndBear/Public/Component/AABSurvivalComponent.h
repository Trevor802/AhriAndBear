// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AABSurvivalComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UAABSurvivalComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAABSurvivalComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Health")
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Survival | Health")
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWhite, Category = "Character | Survival | Health")
	float HealthChangeRate = -1.f;

	// Thirst-related stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Thirst")
	float MaxThirst = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Survival | Thirst")
	float CurrentThirst;
	UPROPERTY(EditAnywhere, BlueprintReadWhite, Category = "Character | Survival | Thirst")
	float ThirstChangeRate = -1.f;

	// Hunger-related stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Hunger")
	float MaxFullness = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Survival | Hunger")
	float CurrentFullness;
	UPROPERTY(EditAnywhere, BlueprintReadWhite, Category = "Character | Survival | Hunger")
	float FullnessChangeRate = -1.f;

	// Warmth-related stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character | Survival | Warmth")
	float MaxWarmth = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Survival | Warmth")
	float CurrentWarmth;
	UPROPERTY(EditAnywhere, BlueprintReadWhite, Category = "Character | Survival | Warmth")
	float WarmthChangeRate = -1.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
