// Fill out your copyright notice in the Description page of Project Settings.


#include "BobbyEnemy.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ABobbyEnemy::ABobbyEnemy() : Super()
{
}

void ABobbyEnemy::BeginPlay()
{
	Super::BeginPlay();

	AController* controller = GetController();
	UActorComponent* actorComponent = controller->GetComponentByClass(UAIPerceptionComponent::StaticClass());
	_perceptionComponent = Cast<UAIPerceptionComponent>(actorComponent);
}

void ABobbyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABobbyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABobbyEnemy::AttackPlayer(AActor* playerActor)
{
}

void ABobbyEnemy::AlertEnemy(AActor* playerActor)
{
}

void ABobbyEnemy::SetAttackLookAngle()
{
	FAISenseID senseId = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	UAISenseConfig* aiSenseConfig = _perceptionComponent->GetSenseConfig(senseId);
	UAISenseConfig_Sight* sightConfig = Cast<UAISenseConfig_Sight>(aiSenseConfig);

	sightConfig->PeripheralVisionAngleDegrees = AttackLookAngle;
	_perceptionComponent->RequestStimuliListenerUpdate();
}

void ABobbyEnemy::SetDefaultLookAngle()
{
	FAISenseID senseId = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	UAISenseConfig* aiSenseConfig = _perceptionComponent->GetSenseConfig(senseId);
	UAISenseConfig_Sight* sightConfig = Cast<UAISenseConfig_Sight>(aiSenseConfig);

	sightConfig->PeripheralVisionAngleDegrees = DefaultLookAngle;
	_perceptionComponent->RequestStimuliListenerUpdate();
}

void ABobbyEnemy::SetSearchLookAngle()
{
	FAISenseID senseId = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	UAISenseConfig* aiSenseConfig = _perceptionComponent->GetSenseConfig(senseId);
	UAISenseConfig_Sight* sightConfig = Cast<UAISenseConfig_Sight>(aiSenseConfig);

	sightConfig->PeripheralVisionAngleDegrees = SearchLookAngle;
	_perceptionComponent->RequestStimuliListenerUpdate();
}