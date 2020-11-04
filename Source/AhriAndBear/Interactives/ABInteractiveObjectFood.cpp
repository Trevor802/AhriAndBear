// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectFood.h"
#include "Engine.h"
#include "Engine/StaticMesh.h"
#include "Engine/CollisionProfile.h"
#include "Components/BoxComponent.h"
#include "Interactives/EventTrigger.h"
#include "GameBase/Define.h"
#include "EventTrigger.h"
#include "ABAnimalCharacter.h"
#include "AABSurvivalComponent.h"
#include "ABSurvivalStats.h"
#include "Components/WidgetComponent.h"


void AABInteractiveObjectFood::BeginPlay()
{
	Super::BeginPlay();
	EventTrigger->EventData.TriggerEvent = EEventType::Supply;
	EventTrigger->EventData.SurvivalData = SurvivalEffect;
}

AABInteractiveObjectFood::AABInteractiveObjectFood()
	: Super()
{

	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionShape;

	FoodMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh1"));
	FoodMesh1->SetupAttachment(RootComponent);
	FoodMesh1->SetCollisionProfileName(TEXT("NoCollision"));

	FoodMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh2"));
	FoodMesh2->SetupAttachment(RootComponent);
	FoodMesh2->SetCollisionProfileName(TEXT("NoCollision"));

	FoodMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh3"));
	FoodMesh3->SetupAttachment(RootComponent);
	FoodMesh3->SetCollisionProfileName(TEXT("NoCollision"));

	FoodArray.Add(FoodMesh1);
	FoodArray.Add(FoodMesh2);
	FoodArray.Add(FoodMesh3);

	bCanBeInteracted = true;
}

// Called every frame
void AABInteractiveObjectFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABInteractiveObjectFood::AfterInteraction()
{

	if (FoodArray.Num() != 0)
	{
		UABSurvivalStatFunctions::AddToCurrentValue(OverlappingAnimal->SurvivalComponent->Hunger, SurvivalEffect.Hunger);

		FindComponentByClass<UEventTrigger>()->Interact(OverlappingAnimal);
		//TODO: play eating sound

		FoodArray[0]->SetVisibility(false);
		FoodArray.RemoveAt(0);
	}
	else
	{
		bCanBeInteracted = false;
	}
}