// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimalAIController.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <BehaviorTree\Blackboard\BlackboardKeyType_Object.h>

AABAnimalAIController::AABAnimalAIController()
	: Super()
{
	PlayerCharacterKey = "Target";
	//Initialize the behavior tree and blackboard components
	//DefaultBehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("BehaviorTree"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	bBlackBoardSet = false;
}

void AABAnimalAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AABAnimalAIController::Tick(float DeltaTime)
{
	if (bBlackBoardSet == false)
	{
		SetBlackBoardTarget();
	}
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
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABAnimalCharacter::StaticClass(), FoundActors);

	for (AActor* animal : FoundActors) {
		if (this != animal) {
			PlayerCharacter = Cast<AABAnimalCharacter>(animal);
		}
	}

	if (PlayerCharacter)
	{
		BlackBoardComp->SetValue<UBlackboardKeyType_Object>(PlayerCharacterKey, PlayerCharacter);
		bBlackBoardSet = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BB set"));
	}
}
