// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BtTaskChaseActor.generated.h"

UCLASS()
class AHRIANDBEAR_API UBtTaskChaseActor : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(Category = "AI", EditAnywhere)
		FName KeyTarget;

	UPROPERTY(Category = "AI", EditAnywhere)
		USoundBase* SoundObject;

	float _lastPlaySec;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; // Receive Execute AI
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override; // Receive Tick AI
};
