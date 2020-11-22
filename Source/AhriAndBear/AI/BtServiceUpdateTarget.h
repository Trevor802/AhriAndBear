// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BtServiceUpdateTarget.generated.h"

/**
 *
 */
UCLASS()
class AHRIANDBEAR_API UBtServiceUpdateTarget : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(Category = "BlackboardKeys", EditAnywhere)
		FName KeyTarget;

	UPROPERTY(Category = "BlackboardKeys", EditAnywhere)
		FName KeyLastPosition;

	UPROPERTY(Category = "BlackboardKeys", EditAnywhere)
		FName KeyDefaultPosition;
	 
	UPROPERTY(Category = "BlackboardKeys", EditAnywhere)
		FName KeyBarkPosition;

	UPROPERTY(Category = "Distance", EditAnywhere)
		float MaxSenseDistance;

	UBlackboardComponent* _blackboardComponent;

protected:

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
		void HandleAnimalBarked(FVector Position);
};
