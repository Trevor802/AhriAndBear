// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPulley.h"
#include "Components/SphereComponent.h"

// Sets default values
AFixedPulley::AFixedPulley()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Start = CreateDefaultSubobject<USphereComponent>(TEXT("Start"));
	Start->SetupAttachment(RootComponent);
	End = CreateDefaultSubobject<USphereComponent>(TEXT("End"));
	End->SetupAttachment(RootComponent);
	CableStart = CreateDefaultSubobject<UCableComponent>(TEXT("CalbeStart"));
	CableStart->SetupAttachment(RootComponent);
	CableStart->EndLocation = FVector::ZeroVector;
	CableEnd = CreateDefaultSubobject<UCableComponent>(TEXT("CalbeEnd"));
	CableEnd->SetupAttachment(RootComponent);
	CableEnd->EndLocation = FVector::ZeroVector;
	Start->SetRelativeLocation(FVector(0, 0, -1) * TotalLength / 2);
	End->SetRelativeLocation(FVector(0, 0, -1) * TotalLength / 2);
}

// Called when the game starts or when spawned
void AFixedPulley::BeginPlay()
{
	Super::BeginPlay();
	
	CableStart->SetAttachEndToComponent(Start);
	CableEnd->SetAttachEndToComponent(End);
}

// Called every frame
void AFixedPulley::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float startLength = Start->GetRelativeLocation().Size();
	float endLength = FMath::Clamp(TotalLength - startLength, 10.0f, TotalLength / 2);
	CableEnd->CableLength = endLength;
	End->SetRelativeLocation(FVector(0, 0, -1) * endLength);
}

