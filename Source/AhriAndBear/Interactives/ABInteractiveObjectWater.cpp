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

	bCanBeInteracted = true;
}

void AABInteractiveObjectWater::Tick(float DeltaTime)
{

}

void AABInteractiveObjectWater::AfterInteraction()
{
	Super::AfterInteraction();

	//TODO: add to survival data
	//TODO: play drinking sound
}
