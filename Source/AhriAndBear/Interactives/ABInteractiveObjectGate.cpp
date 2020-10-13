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

	IteractiveObjectTypes = EABIteractiveObjectTypes::Gate;

	bOpened = false;
}

void AABInteractiveObjectGate::Tick(float DeltaTime)
{
	CheckGateStatus();
}

void AABInteractiveObjectGate::CheckGateStatus()
{
	if (bInteracted == true && bOpened == false)
	{
		//TODO: play gate sound

		//TODO: Release joint or something to open the gate

		bOpened = true;
		bInteracted = false;
	}
}
