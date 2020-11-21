// Fill out your copyright notice in the Description page of Project Settings.


#include "BtTaskPatrol.h"
#include "ShopKeeperController.h"
#include "Characters/ShopKeeper.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBtTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShopKeeperController* shopKeeperController = Cast<AShopKeeperController>(OwnerComp.GetAIOwner());
	if (shopKeeperController != nullptr)
	{
		auto shopKeeperPawn = shopKeeperController->GetPawn();
		AShopKeeper* shopKeeper = Cast<AShopKeeper>(shopKeeperPawn);

		auto patrolPositions = shopKeeper->GetPatrolPositions();
		UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();

		bool isLastPositionSet = blackboardComponent->IsVectorValueSet(KeyLastPosition);
		if (isLastPositionSet)
		{
			auto lastPosition = blackboardComponent->GetValueAsVector(KeyLastPosition);
			blackboardComponent->SetValueAsVector(KeyPatrolPosition, lastPosition);

			blackboardComponent->ClearValue(KeyLastPosition);
		}
		else {
			int randomIndex = FMath::RandRange(0, patrolPositions.Num() - 1);
			blackboardComponent->SetValueAsVector(KeyPatrolPosition, patrolPositions[randomIndex]->GetActorLocation());
		}
	}

	return EBTNodeResult::Succeeded;
}
