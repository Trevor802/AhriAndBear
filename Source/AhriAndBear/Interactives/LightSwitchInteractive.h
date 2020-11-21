// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/OccupyingInteractive.h"
#include "LightSwitchInteractive.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API ALightSwitchInteractive : public AOccupyingInteractive
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	TArray<class ALight*> Lights;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bDefaultOn;
protected:
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent*) const override { return true; }
	virtual void BeginPlay() override;

	virtual void EndInteraction(bool);
private:
	void SwitchAllLights(bool);
	bool bCurrentOn;
};
