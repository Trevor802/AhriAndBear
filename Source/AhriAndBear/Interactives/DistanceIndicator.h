// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DistanceIndicator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class AHRIANDBEAR_API UDistanceIndicator : public UWidgetComponent
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor TextColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FString TextDisplay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float RangeDistance = 500.f;

private:
	bool bInRange = false;
	void InjectData();
	void UpdateTransform();
};
