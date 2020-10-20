// Fill out your copyright notice in the Description page of Project Settings.


#include "BtTaskChaseActor.h"
#include "ShopKeeperController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBtTaskChaseActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	float gameTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	float diff = gameTime - _lastPlaySec;
	if (diff > 5) {
		AShopKeeperController* shopKeeperController = Cast<AShopKeeperController>(OwnerComp.GetAIOwner());
		FVector actorLocation = shopKeeperController->GetPawn()->GetActorLocation();

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundObject, actorLocation, FRotator::ZeroRotator);
		_lastPlaySec = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	}

	return EBTNodeResult::Type::Succeeded;
}

void UBtTaskChaseActor::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	UBlackboardComponent* blackBoardComponent = OwnerComp.GetBlackboardComponent();
	AActor* actor = Cast<AActor>(blackBoardComponent->GetValueAsObject(KeyTarget));
	
	AShopKeeperController* shopKeeperController = Cast<AShopKeeperController>(OwnerComp.GetAIOwner());

	if (actor != nullptr) {
		shopKeeperController->MoveToActor(actor);
	}
}