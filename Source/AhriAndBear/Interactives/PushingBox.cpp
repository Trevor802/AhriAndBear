// Fill out your copyright notice in the Description page of Project Settings.


#include "PushingBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

APushingBox::APushingBox()
{
	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	RootComponent = boxMesh;
	trigger_h = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Horizontal"));
	trigger_h->SetupAttachment(RootComponent);
	trigger_v = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Vertical"));
	trigger_v->SetupAttachment(RootComponent);

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
}

void APushingBox::CallMoveForward(float)
{

}