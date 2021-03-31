// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactives/ABInteractiveBike.h"
#include "ABAnimalCharacter.h"
#include "ABPlayerController.h"
#include "Characters/ABCatCharacter.h"
#include "Characters/ABDogCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"

AABInteractiveBike::AABInteractiveBike()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bike Trigger"));
	BikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BikeMesh"));

	RootComponent = Collider;
	BikeMesh->SetupAttachment(RootComponent);

	bMoving = false;
	bCanMove = true;

	BikeSpeed = 400.0f;
}

void AABInteractiveBike::MoveBike(float DeltaTime)
{
	if (BikePathPoints.Num() != 0)
	{
		FVector CurrentPosition = FMath::VInterpConstantTo(GetActorLocation(), BikePathPoints[PathIndex]->GetActorLocation(), DeltaTime, BikeSpeed);
		SetActorLocation(CurrentPosition);
		IncrementPathIndex(GetActorLocation(), BikePathPoints[PathIndex]->GetActorLocation());
	}
}

void AABInteractiveBike::IncrementPathIndex(FVector BikeLocation, FVector TargetLocation)
{
	if (FVector::Dist(BikeLocation, TargetLocation) <= 0.1f)
	{

		if (PathIndex >= BikePathPoints.Num())
		{
			bCanMove = false;
		}
		else
		{
			PathIndex++;
		}
		AfterInteraction(true);
	}
}

void AABInteractiveBike::BeginPlay()
{
	Super::BeginPlay();

}

void AABInteractiveBike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMoving)
	{
		MoveBike(DeltaTime);
	}
}

void AABInteractiveBike::BeginInteraction()
{
	bMoving = true;
}

void AABInteractiveBike::EndInteraction(bool)
{
	bMoving = false;
}

bool AABInteractiveBike::CanInteract(UCharacterInteractionComponent* interactingComponent) const
{
	if (!Super::CanInteract(interactingComponent)) {
		return false;
	}

	if (!bCanMove)
	{
		return false;
	}

	auto character = GET_CHARACTER(interactingComponent);
	AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
	if (!dogCharacter)
	{
		return false;
	}

	return true;
}

void AABInteractiveBike::CallInteract()
{
}
