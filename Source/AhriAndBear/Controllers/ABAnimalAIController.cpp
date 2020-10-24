// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimalAIController.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <BehaviorTree\Blackboard\BlackboardKeyType_Object.h>
#include <BehaviorTree\Blackboard\BlackboardKeyType_Bool.h>

AABAnimalAIController::AABAnimalAIController()
	: Super()
{
	PlayerCharacterKey = "Target";
	IsFollowingKey = "IsFollowing";
	//Initialize the behavior tree and blackboard components
	//DefaultBehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("BehaviorTree"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AABAnimalAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AABAnimalAIController::Tick(float DeltaTime)
{
	if (AICharacter && AICharacter->bBlackBoardSet == false)
	{
		SetBlackBoardTarget();
	}

	SetBlackBoardFollowing();
}

void AABAnimalAIController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);

	//get reference to character
	AICharacter = Cast<AABAnimalCharacter>(Pawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackBoardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}
		//SetBlackBoardTarget();
		BehaviorTreeComp->StartTree(*AICharacter->BehaviorTree);
	}
}

void AABAnimalAIController::SetBlackBoardTarget()
{
	if (AICharacter)
	{
		BlackBoardComp->SetValue<UBlackboardKeyType_Object>(PlayerCharacterKey, AICharacter->OtherAnimal);
		AICharacter->bBlackBoardSet = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BB set"));
	}
}

void AABAnimalAIController::SetBlackBoardFollowing()
{
	if (AICharacter)
	{
		BlackBoardComp->SetValue<UBlackboardKeyType_Bool>(IsFollowingKey, AICharacter->bIsFollowing);
	}
}
