// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectWater.h"
#include "Engine.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
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

}

void AABInteractiveObjectWater::AfterInteraction()
{
	Super::AfterInteraction();

	//TODO: add to survival data
	FindComponentByClass<UEventTrigger>()->Interact(OverlappingAnimal);
	//TODO: play drinking sound
}
