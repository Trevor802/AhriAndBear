// Fill out your copyright notice in the Description page of Project Settings.


#include "ABDogCharacter.h"
#include "ABCatCharacter.h"
#include "ABPlayerController.h"
#include "Environments/ABScentTrail.h"

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

	PawnSensingComponent->bHearNoises = true;
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AABDogCharacter::HandleSeePawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AABDogCharacter::HandleHearNoise);
}

void AABDogCharacter::UseAbility()
{
	Super::UseAbility();

	//Xiubo, Add Scent Here ~ ~    xb: OK
	UE_LOG(LogTemp, Warning, TEXT("???"));
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABScentTrail::StaticClass(), FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++)
	{
		AABScentTrail* scent = Cast<AABScentTrail>(FoundActors[i]);

		scent->ShowTrail();
	}
}

void AABDogCharacter::HandleSeePawn(APawn* Pawn)
{
	MoveToTargetActor(Pawn);
}

void AABDogCharacter::HandleHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	MoveToTargetActor(OtherActor);
}

void AABDogCharacter::MoveToTargetActor(APawn* Pawn)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AABPlayerController* characterController = Cast<AABPlayerController>(playerController);

	EAnimalType animalType = characterController->AnimalCharacter->AnimalType;
	if (animalType == EAnimalType::Cat && characterController->AnimalCharacter->IsFollowing) {
		AABCatCharacter* catCharacter = Cast<AABCatCharacter>(Pawn);
		if (catCharacter != nullptr) {
			// TODO: Implement AIMoveTo
		}
	}
}
