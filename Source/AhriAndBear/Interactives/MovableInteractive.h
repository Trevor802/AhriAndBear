// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "MovableInteractive.generated.h"

/**
 * 
 */
class AABPlayerController;
UCLASS()
class AHRIANDBEAR_API AMovableInteractive : public AABInteractiveObjectBase
{
	GENERATED_BODY()
protected:
	virtual void AfterInteraction(bool) override;
	virtual bool TryInteracting(UCharacterInteractionComponent*) override;
	virtual void BindInput(AABPlayerController*) const;
	virtual void UnbindInput(AABPlayerController*) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	bool bOccupyMouth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	bool bOccupyPaw;
};
