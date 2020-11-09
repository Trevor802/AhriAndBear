// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectWater.h"
#include "Engine.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "ABAnimalCharacter.h"
#include "AABSurvivalComponent.h"
#include "ABSurvivalStats.h"
#include "EventTrigger.h"

AABInteractiveObjectWater::AABInteractiveObjectWater()
	: Super()
{
	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionShape;
	BowlMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowlMesh"));
	BowlMesh->SetupAttachment(RootComponent);

}

void AABInteractiveObjectWater::BeginPlay()
{
	Super::BeginPlay();
}

void AABInteractiveObjectWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABInteractiveObjectWater::AfterInteraction(bool bResult)
{
	//TODO: add to survival data

	//TODO: play drinking sound
}
