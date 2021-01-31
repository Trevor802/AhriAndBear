// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectNewspaper.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"

AABInteractiveObjectNewspaper::AABInteractiveObjectNewspaper()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	NewspaperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NewspaperMesh"));

	RootComponent = CollisionShape;
	NewspaperMesh->SetupAttachment(RootComponent);

	bOpened = false;
}

void AABInteractiveObjectNewspaper::BeginPlay()
{
	Super::BeginPlay();

}

void AABInteractiveObjectNewspaper::EndInteraction(bool bResult)
{
	Super::EndInteraction(bResult);

	if (!bResult)
	{
		return;
	}

	OpenNewspaper();
}

void AABInteractiveObjectNewspaper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABInteractiveObjectNewspaper::OpenNewspaper()
{
	//NewspaperWidget->addtov;

}
