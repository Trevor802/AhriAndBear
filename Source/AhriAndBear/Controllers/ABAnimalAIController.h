// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "ABAnimalCharacter.h"
#include "ABAnimalAIController.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABAnimalAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AABAnimalAIController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* Pawn) override;
	void SetBlackBoardTarget();
	void SetBlackBoardFollowing();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		UBlackboardComponent* BlackBoardComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		FName PlayerCharacterKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		FName IsFollowingKey;

private:
	AABAnimalCharacter* AICharacter;
};
