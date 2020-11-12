// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BtTaskClearKey.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API UBtTaskClearKey : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(Category = "AI", EditAnywhere)
		FName KeyToClear;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; // Receive Execute AI
};
