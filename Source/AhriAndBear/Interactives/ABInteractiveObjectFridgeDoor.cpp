// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectFridgeDoor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterInteractionComponent.h"
#include "Characters/ABCatCharacter.h"
#include "Characters/ABDogCharacter.h"

AABInteractiveObjectFridgeDoor::AABInteractiveObjectFridgeDoor()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));

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

bool AABInteractiveObjectFridgeDoor::CanInteract(UCharacterInteractionComponent* interactingComponent) const
{
	if (!Super::CanInteract(interactingComponent)) {
		return false;
	}

	auto character = Cast<AABAnimalCharacter>(interactingComponent->GetOwner());

	if (UnlockDirection != FVector::ZeroVector) {
		// Get vector from actor to gate and compare to the UnlockDirection.
		auto actorLocation = character->GetTransform().GetLocation();

		auto gateLocation = GetTransform().GetLocation();
		auto actor2GateVector = gateLocation - actorLocation;
		auto a2gvDotUd = FVector::DotProduct(actor2GateVector, UnlockDirection);

		// Get actor's forward vector and compare to UnlockDirection.
		auto actorForward = character->GetActorForwardVector();
		auto aFDotUd = FVector::DotProduct(actorForward, UnlockDirection);

		// All three vectors should be facing the same direction, meaning neither dot
		// product should be less than zero.
		if (aFDotUd < 0 || a2gvDotUd < 0)
			return false;
	}

	if (bOpened)
	{
		return false;
	}

	return true;
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

	//AddActorLocalRotation(Rotation, false, 0, ETeleportType::None);

	DoorMesh->AddLocalRotation(Rotation, false, 0, ETeleportType::None);
}

void AABInteractiveObjectFridgeDoor::StopRotation()
{
	bOpening = false;
}
