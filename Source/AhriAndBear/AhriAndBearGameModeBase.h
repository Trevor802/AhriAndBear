// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AhriAndBearGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AAhriAndBearGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tasks")
		TArray<FString> LevelTasks;
	UPROPERTY(BlueprintReadOnly, Category = "Tasks")
		FString CurTaskText;

	int CurTaskIndex;

public:
	AAhriAndBearGameModeBase();
	virtual void BeginPlay() override;
	void ToNextTask();
};
