// Fill out your copyright notice in the Description page of Project Settings.


#include "BtTaskClearKey.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBtTaskClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent* blackBoardComponent = OwnerComp.GetBlackboardComponent();
	blackBoardComponent->ClearValue(KetToClear);

	return EBTNodeResult::Succeeded;
}