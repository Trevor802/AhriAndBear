// Fill out your copyright notice in the Description page of Project Settings.


#include "ABScentTrail.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AABScentTrail::AABScentTrail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
 
	spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = spline;
}

// Called when the game starts or when spawned
void AABScentTrail::BeginPlay()
{
	Super::BeginPlay();
	
	InitTrail();
}

// Called every frame
void AABScentTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABScentTrail::InitTrail()
{
	// Calculate the positions along the spline to generate scent Niagara System
	int niagaraQuantity = (int)floor(spline->GetSplineLength() / Interval);

	// Generate Niagara System along the spline
	for (size_t i = 0; i < niagaraQuantity; i++)
	{
		float distance = Interval * i;
		FVector position = spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
		UNiagaraComponent* tempSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TemplateSystem, position, FRotator::ZeroRotator, (FVector)1.0f, false);
		tempSystem->Deactivate();
		systemArray.Add(tempSystem);
	}
}

void AABScentTrail::ShowTrail()
{
	for (int i = 0; i < systemArray.Num(); i++)
	{
		systemArray[i]->Activate(true);
	}
}