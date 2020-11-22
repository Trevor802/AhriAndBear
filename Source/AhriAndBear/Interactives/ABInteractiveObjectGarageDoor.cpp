// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectGarageDoor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AABInteractiveObjectGarageDoor::AABInteractiveObjectGarageDoor()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	
	//RootComponent = Spline;
	//CollisionShape->SetupAttachment(RootComponent);
	//DoorMesh->SetupAttachment(RootComponent);
	//ButtonMesh->SetupAttachment(RootComponent);

	bOpened = false;
}

void AABInteractiveObjectGarageDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABInteractiveObjectGarageDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOpened == true)
	{
		OpenDoor();
	}
}

void AABInteractiveObjectGarageDoor::EndInteraction(bool bResult)
{
	Super::EndInteraction(bResult);

	if (!bResult)
	{
		return;
	}

	StartTime = GetWorld()->GetTimeSeconds();
	bOpened = true;
}

void AABInteractiveObjectGarageDoor::OpenDoor()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gate Opened"));

	float currentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTime;

	float distance = Spline->GetSplineLength() * currentSplineTime;

	FVector position = Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	DoorMesh->SetWorldLocation(position);

	FVector rotation = Spline->GetDirectionAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);

	FRotator Rotator = FRotationMatrix::MakeFromX(rotation).Rotator();

	//DoorMesh->SetWorldRotation(Rotator);
}

