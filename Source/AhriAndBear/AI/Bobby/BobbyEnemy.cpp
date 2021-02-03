// Fill out your copyright notice in the Description page of Project Settings.


#include "BobbyEnemy.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

ABobbyEnemy::ABobbyEnemy() : Super()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));

	SightConfig->PeripheralVisionAngleDegrees = 45;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->SightRadius = 750;
	SightConfig->LoseSightRadius = 900;
	SightConfig->SetMaxAge(1);
	PerceptionComponent->ConfigureSense(*SightConfig);

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->HearingRange = 1000;
	HearingConfig->SetMaxAge(7);
	PerceptionComponent->ConfigureSense(*HearingConfig);

	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

}

void ABobbyEnemy::BeginPlay()
{
	Super::BeginPlay();
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
	UAISenseConfig* aiSenseConfig = PerceptionComponent->GetSenseConfig(senseId);
	UAISenseConfig_Sight* sightConfig = Cast<UAISenseConfig_Sight>(aiSenseConfig);

	sightConfig->PeripheralVisionAngleDegrees = AttackLookAngle;
	PerceptionComponent->RequestStimuliListenerUpdate();
}

void ABobbyEnemy::SetDefaultLookAngle()
{
	FAISenseID senseId = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	UAISenseConfig* aiSenseConfig = PerceptionComponent->GetSenseConfig(senseId);
	UAISenseConfig_Sight* sightConfig = Cast<UAISenseConfig_Sight>(aiSenseConfig);

	sightConfig->PeripheralVisionAngleDegrees = DefaultLookAngle;
	PerceptionComponent->RequestStimuliListenerUpdate();
}

void ABobbyEnemy::SetSearchLookAngle()
{
	FAISenseID senseId = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	UAISenseConfig* aiSenseConfig = PerceptionComponent->GetSenseConfig(senseId);
	UAISenseConfig_Sight* sightConfig = Cast<UAISenseConfig_Sight>(aiSenseConfig);

	sightConfig->PeripheralVisionAngleDegrees = SearchLookAngle;
	PerceptionComponent->RequestStimuliListenerUpdate();
}