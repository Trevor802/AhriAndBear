// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BtDecoratorInCone.generated.h"

UCLASS()
class AHRIANDBEAR_API UBtDecoratorInCone : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(Category = "AI", EditAnywhere)
		float HalfAngle;
	
public:
	bool PerformConditionCheckAI(AAIController* ownerController, ACharacter* controlledPawn);
};
