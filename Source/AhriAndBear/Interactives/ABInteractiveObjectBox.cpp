// Fill out your copyright notice in the Description page of Project Settings.

#include "ABInteractiveObjectBox.h"
#include "Components/BoxComponent.h"
#include "ABAnimalCharacter.h"
#include "Components/PrimitiveComponent.h"

AABInteractiveObjectBox::AABInteractiveObjectBox()
{
	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = boxMesh;

	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionShape->SetupAttachment(RootComponent);

}

void AABInteractiveObjectBox::Tick(float DeltaTime)
{

}

void AABInteractiveObjectBox::OnActorEnter(AActor* OtherActor)
{

}

void AABInteractiveObjectBox::OnActorExit(AActor* OtherActor)
{

}