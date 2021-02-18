// Fill out your copyright notice in the Description page of Project Settings.


#include "CrierEnemy.h"

#include "Perception/AIPerceptionComponent.h"

ACrierEnemy::ACrierEnemy() : Super()
{
}

void ACrierEnemy::BeginPlay()
{
	Super::BeginPlay();

	AController* controller = GetController();
	UActorComponent* actorComponent = controller->GetComponentByClass(UAIPerceptionComponent::StaticClass());
	_perceptionComponent = Cast<UAIPerceptionComponent>(actorComponent);
}

void ACrierEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACrierEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}