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

	bOpened = false;

	bCanBeInteracted = true;
}

void AABInteractiveObjectGate::Tick(float DeltaTime)
{

}

void AABInteractiveObjectGate::AfterInteraction()
{
	if (bOpened == false)
	{
		//TODO: play gate sound

		//TODO: Release joint or something to open the gate

		bOpened = true;
		bCanBeInteracted = false;
	}
}
