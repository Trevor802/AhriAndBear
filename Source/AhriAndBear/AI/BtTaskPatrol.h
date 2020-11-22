// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BtTaskPatrol.generated.h"

/**
 *
 */
UCLASS()
class AHRIANDBEAR_API UBtTaskPatrol : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(Category = "AI", EditAnywhere)
		FName KeyPatrolPosition;

	UPROPERTY(Category = "AI", EditAnywhere)
		FName KeyLastPosition;

	int _currentIndex = 0;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; // Receive Execute AI
};
