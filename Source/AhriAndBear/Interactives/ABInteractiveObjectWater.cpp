// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectWater.h"
#include "Engine.h"
#include "Engine/StaticMesh.h"
#include "Engine/CollisionProfile.h"

AABInteractiveObjectWater::AABInteractiveObjectWater()
	: Super()
{
	BowlMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowlMesh"));
	BowlMesh->SetupAttachment(RootComponent);

	IteractiveObjectTypes = EABIteractiveObjectTypes::Water;
}

void AABInteractiveObjectWater::Tick(float DeltaTime)
{
	CheckWaterStatus();
}

void AABInteractiveObjectWater::CheckWaterStatus()
{
	if (bInteracted == true)
	{
		//TODO: add to survival data

		//TODO: play drinking sound

		bInteracted = false;
	}
}
