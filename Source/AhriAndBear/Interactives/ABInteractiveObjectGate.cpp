// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectGate.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"

AABInteractiveObjectGate::AABInteractiveObjectGate()
	: Super()
{
	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionShape;

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
	GateMesh->SetupAttachment(RootComponent);

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(RootComponent);

	DoorJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("DoorJoint"));
	DoorJoint->SetupAttachment(RootComponent);
	DoorJoint->SetDisableCollision(true);

	bCanBeInteracted = true;
}

void AABInteractiveObjectGate::BeginPlay()
{
	Super::BeginPlay();
	EventTrigger->EventData.TriggerEvent = EEventType::Nothing;
}

void AABInteractiveObjectGate::Tick(float DeltaTime)
{

}

void AABInteractiveObjectGate::AfterInteraction()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Door Unlocked"));
	DoorJoint->SetDisableCollision(false);
	bCanBeInteracted = false;
}
