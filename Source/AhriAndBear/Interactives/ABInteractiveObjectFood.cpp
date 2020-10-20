// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectFood.h"
#include "Engine.h"
#include "Engine/StaticMesh.h"
#include "Engine/CollisionProfile.h"
#include "VolumeInteractiveComponent.h"

AABInteractiveObjectFood::AABInteractiveObjectFood()
	: Super()
{
	FoodMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh1"));
	FoodMesh1->SetupAttachment(RootComponent);

	FoodMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh2"));
	FoodMesh2->SetupAttachment(RootComponent);

	FoodMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh3"));
	FoodMesh3->SetupAttachment(RootComponent);

	FoodArray.Add(FoodMesh1);
	FoodArray.Add(FoodMesh2);
	FoodArray.Add(FoodMesh3);

	bCanBeInteracted = true;
}

// Called every frame
void AABInteractiveObjectFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABInteractiveObjectFood::AfterInteraction()
{
	Super::AfterInteraction();

	if (FoodArray.Num() != 0)
	{
		//TODO: add survival data
		FindComponentByClass<UVolumeInteractiveComponent>()->Interact();
		//TODO: play eating sound

		FoodArray[0]->SetVisibility(false);
		FoodArray.RemoveAt(0);
	}
	else
	{
		bCanBeInteracted = false;
	}
}