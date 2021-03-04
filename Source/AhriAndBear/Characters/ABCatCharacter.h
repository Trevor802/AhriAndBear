// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABAnimalCharacter.h"
#include "Components/PostProcessComponent.h"
#include "ABCatCharacter.generated.h"

class UPostProcessComponent;
class AABScentSource;

UCLASS()
class AHRIANDBEAR_API AABCatCharacter : public AABAnimalCharacter
{
	GENERATED_BODY()

public:
	AABCatCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void UseAbility() override;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AABScentSource> scentSourceBP;
	AABScentSource* myScentSource;
	void SetupNVParams();
	void UpdateCatScentSource();

protected:
	virtual void BeginPlay() override;
	EABAnimalMovementNoiseVolume GetSprintMovementVolume() const override { return EABAnimalMovementNoiseVolume::Quiet; }
	virtual EABAnimalMovementNoiseVolume GetCurrentMovementVolume() const override;

private:
	FPostProcessSettings normalSettings;
	FPostProcessSettings nightVisionSettings;
	UPostProcessComponent* postProcess;
	bool abilityOn;
};
