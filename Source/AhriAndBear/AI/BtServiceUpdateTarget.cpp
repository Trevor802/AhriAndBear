// Fill out your copyright notice in the Description page of Project Settings.


#include "BtServiceUpdateTarget.h"
#include "ShopKeeperController.h"
#include "ABAnimalCharacter.h"

#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UBtServiceUpdateTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShopKeeperController* shopKeeperController = Cast<AShopKeeperController>(OwnerComp.GetAIOwner());
	if (shopKeeperController != nullptr) {

		UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();

		FVector actorLocation = shopKeeperController->GetPawn()->GetActorLocation();
		blackboardComponent->SetValueAsVector(KeyDefaultPosition, actorLocation);

		TArray<AActor*> animals = TArray<AActor*>();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABAnimalCharacter::StaticClass(), animals);

		for (int i = 0; i < animals.Num(); i++) {
			if (IsValid(animals[i])) {
				AABAnimalCharacter* animalCharacter = Cast<AABAnimalCharacter>(animals[i]);
				animalCharacter->OnAnimalBark.AddDynamic(this, &UBtServiceUpdateTarget::HandleAnimalBarked);
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

		float angle = blackboardComponent->GetValueAsFloat(KeyPlayerAngle);
		float distance = FVector::Dist(actorLocation, playerLocation);

		if ((angle <= FOVHalfAngle && distance <= MaxDirectSenseDistance) || (angle > FOVHalfAngle && distance <= MaxInDirectSenseDistance))
		{
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
				else
				{
					blackboardComponent->ClearValue(KeyTarget);
				}
			}
		}
		else
		{
			blackboardComponent->ClearValue(KeyTarget);
		}

		_blackboardComponent = blackboardComponent;
	}
}

void UBtServiceUpdateTarget::HandleAnimalBarked(FVector Position)
{
	if (_blackboardComponent != nullptr) {
		_blackboardComponent->SetValueAsVector(KeyBarkPosition, Position);
		_blackboardComponent->SetValueAsVector(KeyLastPosition, FVector::ZeroVector);
	}
}
