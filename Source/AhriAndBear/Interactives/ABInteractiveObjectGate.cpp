// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectGate.h"
#include "Engine/StaticMesh.h"

AABInteractiveObjectGate::AABInteractiveObjectGate()
	: Super()
{
	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
	GateMesh->SetupAttachment(RootComponent);

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(RootComponent);

	DoorJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("DoorJoint"));
	DoorJoint->SetupAttachment(RootComponent);
	DoorJoint->SetDisableCollision(true);

	bCanBeInteracted = true;
}

void AABInteractiveObjectGate::Tick(float DeltaTime)
{

}

void AABInteractiveObjectGate::AfterInteraction()
{
	DoorJoint->SetDisableCollision(false);
	bCanBeInteracted = false;
}
