// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBase/Define.h"
#include "ABStatModifierInterface.h"
#include "ABRestArea.generated.h"

// Forward declares
class UBoxComponent;

UCLASS()
class AHRIANDBEAR_API AABRestArea : public AActor, public IABStatModifierInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABRestArea();

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Rest Area")
	FSurvivalData ChangeRates;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Rest Area")
	UBoxComponent* Collider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void BeginOverlap(AActor* self, AActor* OtherActor);

	UFUNCTION()
	void EndOverlap(AActor* self, AActor* OtherActor);

	bool DoesModifyHungerRate() const override { return ChangeRates.Hunger != 0; }
	
	float GetHungerRateModifier(UAABSurvivalComponent* mainComp, float defaultHungerDelta, float currentDelta) override;

	bool DoesModifyThirstRate() const override { return ChangeRates.Thirst != 0; }
	
	float GetThirstRateModifier(UAABSurvivalComponent* mainComp, float defaultThirstDelta, float currentDelta) override;
};
