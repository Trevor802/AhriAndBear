// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectFood.h"
#include "Engine.h"
#include "Engine/StaticMesh.h"
#include "Engine/CollisionProfile.h"

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

	IteractiveObjectTypes = EABIteractiveObjectTypes::Food;
}

// Called every frame
void AABInteractiveObjectFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFoodStatus();
}

void AABInteractiveObjectFood::CheckFoodStatus() 
{
	if (bInteracted == true && FoodArray.Num() != 0)
	{
		//TODO: add to survival data

		//TODO: play eating sound

		FoodArray[0]->SetVisibility(false);
		FoodArray.RemoveAt(0);

		bInteracted = false;
	}
}