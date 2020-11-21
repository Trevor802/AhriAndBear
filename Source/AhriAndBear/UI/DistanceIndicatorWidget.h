// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DistanceIndicatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API UDistanceIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	AActor* ActorAttaching;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FString TextToDisplay;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	float Distance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	bool bInRange;

	UFUNCTION(BlueprintImplementableEvent)
		void OnEnterRange();
	UFUNCTION(BlueprintImplementableEvent)
		void OnExitRange();
};
