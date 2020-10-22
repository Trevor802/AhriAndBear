// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "ABInteractiveObjectPlaySound.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectPlaySound : public AABInteractiveObjectBase
{
	GENERATED_BODY()
public:
	AABInteractiveObjectPlaySound();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound")
	class UAudioComponent* Sound;

	virtual void OnActorEnter(AActor*) override;
	virtual void OnActorExit(AActor*) override;
};
