// Fill out your copyright notice in the Description page of Project Settings.


#include "BobbyEnemy.h"

#include "Perception/AIPerceptionComponent.h"

ABobbyEnemy::ABobbyEnemy() : Super()
{
}

void ABobbyEnemy::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ABobbyEnemy::HandlePerceptionUpdated);
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

void ABobbyEnemy::HandlePerceptionUpdated(const TArray<AActor*>& Actors)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Perception Updated");
}