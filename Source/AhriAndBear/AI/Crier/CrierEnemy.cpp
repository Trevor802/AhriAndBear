// Fill out your copyright notice in the Description page of Project Settings.


#include "CrierEnemy.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

ACrierEnemy::ACrierEnemy() : Super()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));

	SightConfig->PeripheralVisionAngleDegrees = 45;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->SightRadius = 350.0f;
	SightConfig->LoseSightRadius = 400.0f;
	SightConfig->SetMaxAge(1);
	PerceptionComponent->ConfigureSense(*SightConfig);

	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->HearingRange = 500.0f;
	HearingConfig->SetMaxAge(7);
	PerceptionComponent->ConfigureSense(*HearingConfig);

	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ACrierEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ACrierEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACrierEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}