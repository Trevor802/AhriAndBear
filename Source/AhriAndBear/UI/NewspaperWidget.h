// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NewspaperWidget.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API UNewspaperWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void Open();
	UFUNCTION(BlueprintImplementableEvent)
		void Close();
};
