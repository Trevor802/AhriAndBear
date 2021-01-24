// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyBase::AEnemyBase()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyBase::AttackPlayer(AActor* playerActor)
{

}

void AEnemyBase::AlertEnemy(AActor* playerActor)
{

}