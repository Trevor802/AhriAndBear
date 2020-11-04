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

	bCanBeInteracted = true;
}

void AABInteractiveObjectWater::BeginPlay()
{
	Super::BeginPlay();
	EventTrigger->EventData.TriggerEvent = EEventType::Supply;
	EventTrigger->EventData.SurvivalData = SurvivalEffect;
}

void AABInteractiveObjectWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABInteractiveObjectWater::AfterInteraction()
{
	//TODO: add to survival data
	UABSurvivalStatFunctions::AddToCurrentValue(OverlappingAnimal->SurvivalComponent->Thirst, SurvivalEffect.Thirst);

	FindComponentByClass<UEventTrigger>()->Interact(OverlappingAnimal);
	//TODO: play drinking sound
}
