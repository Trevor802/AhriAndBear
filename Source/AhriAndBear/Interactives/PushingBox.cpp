// Fill out your copyright notice in the Description page of Project Settings.


#include "PushingBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Interactives/CharacterInteractionComponent.h"
#include "ABAnimalCharacter.h"
#include "ABPlayerController.h"

APushingBox::APushingBox()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	boxMesh->SetupAttachment(RootComponent);
	trigger_h = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Horizontal"));
	trigger_h->SetupAttachment(boxMesh);
	trigger_v = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Vertical"));
	trigger_v->SetupAttachment(boxMesh);

}

void APushingBox::BeginPlay()
{

}

void APushingBox::BeginInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("!?"));

}

void APushingBox::EndInteraction(bool)
{

}

void APushingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateBox();
}

void APushingBox::UpdateBox()
{
	if (InteractingComponent)
	{
		boxMesh->SetWorldLocation(InteractingComponent->GetComponentLocation());
	}
}

void APushingBox::CallMoveForward(float value)
{
	RETURN_IF_NULL(InteractingComponent);
	auto controller = GET_CONTROLLER(InteractingComponent);
	RETURN_IF_NULL(controller);
	auto character = GET_CHARACTER(InteractingComponent);
	controller->CallMoveForward(value);
}

void APushingBox::TogglePushing(bool bStartPushing)
{
	if (bStartPushing)
	{

	}
	else
	{

	}
}