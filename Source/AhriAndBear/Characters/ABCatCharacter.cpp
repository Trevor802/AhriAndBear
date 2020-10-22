// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCatCharacter.h"
#include "ABDogCharacter.h"
#include "ABPlayerController.h"

#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"

#include "Kismet/GameplayStatics.h"

void AABCatCharacter::BeginPlay()
{
	Super::BeginPlay();

	PawnSensingComponent->bHearNoises = true;
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AABCatCharacter::HandleSeePawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AABCatCharacter::HandleHearNoise);
}

void AABCatCharacter::HandleSeePawn(APawn* Pawn)
{
	MoveToTargetActor(Pawn);
}

void AABCatCharacter::HandleHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	MoveToTargetActor(OtherActor);
}

void AABCatCharacter::MoveToTargetActor(APawn* Pawn)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AABPlayerController* characterController = Cast<AABPlayerController>(playerController);
	if (characterController != nullptr) {
		EAnimalType currentAnimal = characterController->AnimalCharacter->AnimalType;

		if (currentAnimal == AnimalType && characterController->AnimalCharacter->IsFollowing) {
			AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(Pawn);

			if (dogCharacter != nullptr) {
				// TODO: Implement AIMoveTo
			}
		}
	}
}
