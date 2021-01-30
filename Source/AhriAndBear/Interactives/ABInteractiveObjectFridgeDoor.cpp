// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectFridgeDoor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AABInteractiveObjectFridgeDoor::AABInteractiveObjectFridgeDoor()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurtainMesh"));

	RootComponent = CollisionShape;
	DoorMesh->SetupAttachment(RootComponent);

	bOpened = false;
	bOpening = false;
	AngleAxis = 0;
}

void AABInteractiveObjectFridgeDoor::BeginPlay()
{
	Super::BeginPlay();

}

void AABInteractiveObjectFridgeDoor::EndInteraction(bool bResult)
{
	Super::EndInteraction(bResult);

	if (!bResult)
	{
		return;
	}

	bOpened = true;
	bOpening = true;

	FTimerDelegate DoorTimerDelegate = FTimerDelegate::CreateUObject(this, &AABInteractiveObjectFridgeDoor::StopRotation);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, DoorTimerDelegate, RotationTimeLength, false);
}

void AABInteractiveObjectFridgeDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOpened == true && bOpening == true)
	{
		OpenDoor();
	}
}

void AABInteractiveObjectFridgeDoor::OpenDoor()
{
	FQuat Rotation = FQuat(FRotator(0.f, RotationRate, 0.f));

	AddActorLocalRotation(Rotation, false, 0, ETeleportType::None);
}

void AABInteractiveObjectFridgeDoor::StopRotation()
{
	bOpening = false;
}
