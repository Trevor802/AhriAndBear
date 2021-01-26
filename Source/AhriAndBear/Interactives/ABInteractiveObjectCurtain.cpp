// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectCurtain.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AABInteractiveObjectCurtain::AABInteractiveObjectCurtain()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CurtainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurtainMesh"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));

	RootComponent = CollisionShape;
	Spline->SetupAttachment(RootComponent);
	CurtainMesh->SetupAttachment(RootComponent);

	bOpened = false;
}

void AABInteractiveObjectCurtain::BeginPlay()
{
	Super::BeginPlay();

}

void AABInteractiveObjectCurtain::EndInteraction(bool bResult)
{
	Super::EndInteraction(bResult);

	if (!bResult)
	{
		return;
	}

	StartTime = GetWorld()->GetTimeSeconds();
	bOpened = true;
}

void AABInteractiveObjectCurtain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOpened == true)
	{
		OpenCurtain();
	}
}

void AABInteractiveObjectCurtain::OpenCurtain()
{
	float currentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTime;

	float distance = Spline->GetSplineLength() * currentSplineTime;

	FVector position = Spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	CurtainMesh->SetWorldLocation(position);

}
