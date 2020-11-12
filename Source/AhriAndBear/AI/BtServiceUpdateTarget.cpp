// Fill out your copyright notice in the Description page of Project Settings.


#include "BtServiceUpdateTarget.h"
#include "ShopKeeperController.h"
#include "ABAnimalCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "BehaviorTree/BlackboardComponent.h"

void UBtServiceUpdateTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShopKeeperController* shopKeeperController = Cast<AShopKeeperController>(OwnerComp.GetAIOwner());
	if (shopKeeperController != nullptr) {

		UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();

		FVector actorLocaion = shopKeeperController->GetPawn()->GetActorLocation();
		blackboardComponent->SetValueAsVector(KeyDefaultPosition, actorLocaion);

		TArray<AActor*> animals = TArray<AActor*>();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABAnimalCharacter::StaticClass(), animals);

		for (int i = 0; i < animals.Num(); i++) {
			if (IsValid(animals[i])) {
				// TODO: Bind Event To OnBark
			}
		}
	}
}

void UBtServiceUpdateTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AShopKeeperController* shopKeeperController = Cast<AShopKeeperController>(OwnerComp.GetAIOwner());
	if (shopKeeperController != nullptr) {

		UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();

		ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		FVector actorLocation = shopKeeperController->GetPawn()->GetActorLocation();
		FVector playerLocation = playerCharacter->GetActorLocation();

		FCollisionShape sphereShape = FCollisionShape::MakeSphere(10); // Probably can be cached
		FHitResult hitResult;

		bool didCollide = GetWorld()->SweepSingleByChannel(hitResult, actorLocation, playerLocation, FQuat::Identity, ECollisionChannel::ECC_Visibility, sphereShape);
		if (didCollide) {
			AActor* hitActor = hitResult.GetActor();
			AABAnimalCharacter* animalCharacter = Cast<AABAnimalCharacter>(hitActor);

			if (animalCharacter != nullptr) {
				blackboardComponent->SetValueAsObject(KeyTarget, playerCharacter);
				blackboardComponent->SetValueAsVector(KeyLastPosition, playerLocation);
			}
			else {
				blackboardComponent->ClearValue(KeyTarget);
			}
		}
	}
}
