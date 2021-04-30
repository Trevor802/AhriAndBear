// Fill out your copyright notice in the Description page of Project Settings.


#include "ABDogCharacter.h"
#include "ABCatCharacter.h"
#include "ABPlayerController.h"
#include "Environments/ABScentTrail.h"
#include "Environments/ABScentSource.h"
#include "Environments/ABScentIndicator.h"

#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"

#include "Kismet/GameplayStatics.h"

AABDogCharacter::AABDogCharacter()
	: Super()
{
}

void AABDogCharacter::BeginPlay()
{
	Super::BeginPlay();
	myIsPushing = false;
}

void AABDogCharacter::UseAbility()
{
	Super::UseAbility();

	//Xiubo, Add Scent Here ~ ~    xb: OK
	//UE_LOG(LogTemp, Warning, TEXT("???"));
	CatScentTracker();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABScentSource::StaticClass(), FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++)
	{
		AABScentSource* scent = Cast<AABScentSource>(FoundActors[i]);

		scent->SpawnScentIndicator(this);
	}
}

void AABDogCharacter::CatScentTracker()
{
	AABCatCharacter* cat = Cast<AABCatCharacter>(OtherAnimal);
	if (cat)
	{
		cat->UpdateCatScentSource();
		if (scentIndicator)
		{
			AABScentIndicator* indicator =
				GetWorld()->SpawnActor<AABScentIndicator>(scentIndicator, GetActorLocation() + FVector(0, 50, 0), GetActorRotation());
			if (cat->myScentSource)
				indicator->SetTargetPosition(cat->myScentSource);
			else
				UE_LOG(LogTemp, Error, TEXT("AABDogCharacter: Cat's scnet source not available."));
			indicator->SetTargetPosition(cat->GetActorLocation());
			indicator->SetIndicatorLifeSpan(3);
			//indicator->CalculateDirection();
		}
		
	}
}

void AABDogCharacter::EnterPushMode()
{
	myIsPushing = true;
}

void AABDogCharacter::SetInteractState(InteractState i_state)
{
	myInteractState = i_state;
}
