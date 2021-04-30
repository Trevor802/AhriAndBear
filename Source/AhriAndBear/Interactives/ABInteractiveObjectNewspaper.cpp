// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectNewspaper.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Interactive.h"
#include "ABPlayerUIComponent.h"
#include "ABAnimalCharacter.h"

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

void AABInteractiveObjectNewspaper::BeginInteraction()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("read news"));
	OpenNewspaper();
}

void AABInteractiveObjectNewspaper::EndInteraction(bool)
{
	auto character = GET_CHARACTER(InteractingComponent);

	AABAnimalCharacter* player = Cast<AABAnimalCharacter>(character);

	if (player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("close news"));
		player->FindComponentByClass<UABPlayerUIComponent>()->RemoveNewspaperWidgetFromViewPort();
	}
}

void AABInteractiveObjectNewspaper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABInteractiveObjectNewspaper::OpenNewspaper()
{
	//NewspaperWidget->addtov;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TempTitle);

	auto character = GET_CHARACTER(InteractingComponent);

	AABAnimalCharacter* player = Cast<AABAnimalCharacter>(character);

	if (player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("player found"));
		player->FindComponentByClass<UABPlayerUIComponent>()->AddNewspaperWidgetToViewPort(NewspaperIndex);
	}
	
}
