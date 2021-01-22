// Fill out your copyright notice in the Description page of Project Settings.


#include "CrierEnemy.h"
#include "../../ABAnimalCharacter.h"

#include "Perception/AIPerceptionComponent.h"

#include "Kismet/GameplayStatics.h"

ACrierEnemy::ACrierEnemy() : Super()
{
}

void ACrierEnemy::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ACrierEnemy::HandlePerceptionUpdated);
}

void ACrierEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAlertCounter(DeltaTime);
}

void ACrierEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACrierEnemy::AttackPlayer(AActor* playerActor)
{
	// Do Nothing...
}

void ACrierEnemy::AlertEnemy(AActor* playerActor)
{

}

void ACrierEnemy::UpdateAlertCounter(float deltaTime)
{
	if (_currentAlertCount > 0)
	{
		_alertDelayTimer -= deltaTime;
		if (_alertDelayTimer <= 0)
		{
			_currentAlertCount -= 1;
			_alertDelayTimer = AlertDelayTime;

			FVector soundLocation = GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnemySound, soundLocation, FRotator::ZeroRotator);
			MakeNoise();

			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Playing Noise At Location: " + FString::SanitizeFloat(_currentAlertCount));
		}
	}
}

void ACrierEnemy::HandlePerceptionUpdated(const TArray<AActor*>& Actors)
{
	bool animalLocated = false;

	for (int i = 0; i < Actors.Num(); i++)
	{
		AABAnimalCharacter* animalCharacter = Cast<AABAnimalCharacter>(Actors[i]);
		if (animalCharacter != nullptr)
		{
			animalLocated = true;
			break;
		}
	}

	if (animalLocated)
	{
		_currentAlertCount = AlertTimesCount;
		_alertDelayTimer = 0;

		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Audio State Updated");
	}
}