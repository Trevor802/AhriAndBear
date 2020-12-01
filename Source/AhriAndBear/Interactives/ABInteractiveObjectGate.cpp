// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectGate.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"
#include "AhriAndBearGameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Interactives/Interactive.h"
#include "Characters/ABCatCharacter.h"

AABInteractiveObjectGate::AABInteractiveObjectGate()
	: Super()
{
	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionShape;

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
	GateMesh->SetupAttachment(RootComponent);

	GateHinge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateHinge"));
	GateHinge->SetupAttachment(RootComponent);
	// Set the hinge mesh to a cylinder
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (CylinderAsset.Succeeded())
	{
		GateHinge->SetStaticMesh(CylinderAsset.Object);
		GateHinge->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		GateHinge->SetWorldScale3D(FVector(0.2f, 0.2f, 2.0f));
		GateHinge->SetHiddenInGame(true);
	}

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(RootComponent);

	DoorJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("DoorJoint"));
	DoorJoint->SetupAttachment(RootComponent);
	DoorJoint->SetDisableCollision(true);

	bCanTriggerTask = false;
	bOpened = false;

}

void AABInteractiveObjectGate::BeginPlay()
{
	Super::BeginPlay();
	GateMesh->SetSimulatePhysics(false);
}

void AABInteractiveObjectGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AABInteractiveObjectGate::CanInteract(UCharacterInteractionComponent* component) const
{
	auto boxComponent = Cast<UBoxComponent>(component);
	auto character = Cast<AABAnimalCharacter>(boxComponent->GetOwner());
	AABCatCharacter* catCharacter = Cast<AABCatCharacter>(character);
	if (catCharacter)
		return !bOpened;
	else
		return false;
}

void AABInteractiveObjectGate::EndInteraction(bool bResult)
{
	Super::EndInteraction(bResult);

	if (!bResult)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Door Unlocked"));
	DoorJoint->SetDisableCollision(false);
	GateMesh->SetSimulatePhysics(true);
	bOpened = true;

	if (bCanTriggerTask)
	{
		AAhriAndBearGameModeBase* GameMode = (AAhriAndBearGameModeBase*)GetWorld()->GetAuthGameMode();
		GameMode->ToNextTask();
	}
}
