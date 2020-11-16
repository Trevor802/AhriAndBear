// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionDurationWidget.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API UInteractionDurationWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginInteraction(float Duration);
	UFUNCTION(BlueprintImplementableEvent)
		void OnEndInteraction(bool bResult);
};
