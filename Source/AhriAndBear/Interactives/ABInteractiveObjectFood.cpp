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
#include "CharacterInteractionComponent.h"
#include "ABSurvivalStats.h"
#include "Components/WidgetComponent.h"


void AABInteractiveObjectFood::BeginPlay()
{
	Super::BeginPlay();
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
}

// Called every frame
void AABInteractiveObjectFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FoodArray.Num() == 0)
	{
		TempGymRespawn();
	}
}

void AABInteractiveObjectFood::EndInteraction(bool bResult)
{
	Super::EndInteraction(bResult);
	if (!bResult)
	{
		return;
	}
	InteractingComponent->GetOwner()->FindComponentByClass<UAABSurvivalComponent>()->AddSurvivalData(SurvivalEffect);
	if (FoodArray.Num() != 0)
	{

		//TODO: play eating sound

		FoodArray[0]->SetVisibility(false);
		FoodArray.RemoveAt(0);
	}
	else
	{
		FTimerDelegate RespawnTimerDelegate = FTimerDelegate::CreateUObject(this, &AABInteractiveObjectFood::TempGymRespawn); // for planet fitness meat heads only
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, RespawnTimerDelegate, 0.5f, false);
	}
}

void AABInteractiveObjectFood::TempGymRespawn() 
{
	FoodArray.Add(FoodMesh1);
	FoodArray.Add(FoodMesh2);
	FoodArray.Add(FoodMesh3);

	FoodMesh1->SetVisibility(true);
	FoodMesh2->SetVisibility(true);
	FoodMesh3->SetVisibility(true);

}