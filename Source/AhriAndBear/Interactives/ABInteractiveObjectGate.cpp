// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectGate.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Interactives/EventTrigger.h"
#include "AhriAndBearGameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Interactives/Interactive.h"
#include "Characters/ABCatCharacter.h"
#include "Characters/ABDogCharacter.h"
#include "CharacterInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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
	bDogCanOpen = true;
	CombinationOnlyOpen = true;
	bCanDogInteract = false;
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
	//auto boxComponent = Cast<UBoxComponent>(component);
	if (!Super::CanInteract(component)) return false;

	auto character = Cast<AABAnimalCharacter>(component->GetOwner());
	AABCatCharacter* catCharacter = Cast<AABCatCharacter>(character);

	TArray<AActor*> animals;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABAnimalCharacter::StaticClass(), animals);
	AABDogCharacter* dogCharacter = nullptr;
	for (int i = 0; i < animals.Num(); i++)
	{
		auto dogActor = Cast<AABDogCharacter>(animals[i]);
		if (dogActor != nullptr)
		{
			dogCharacter = dogActor;
		}
	}

	// Only check directions if the UnlockDirection vector is not the zero  vector.
	if (UnlockDirection != FVector::ZeroVector) {
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Green, TEXT("Checking to see if gate can be unlocked"));
		// Get vector from actor to gate and compare to the UnlockDirection.
		auto actorLocation = character->GetTransform().GetLocation();

		auto gateLocation = GetTransform().GetLocation();
		auto actor2GateVector = gateLocation - actorLocation;
		auto a2gvDotUd = FVector::DotProduct(actor2GateVector, UnlockDirection);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("a2gvDotUd is %f"), a2gvDotUd));
		DrawDebugLine(GetWorld(), actorLocation, gateLocation, FColor::Cyan, false, 1, 0, 5.f);
		// Get actor's forward vector and compare to UnlockDirection.
		auto actorForward = character->GetActorForwardVector();
		auto aFDotUd = FVector::DotProduct(actorForward, UnlockDirection);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("aFDotUd is %f"), aFDotUd));
		// All three vectors should be facing the same direction, meaning neither dot
		// product should be less than zero.

		if (aFDotUd < 0 || a2gvDotUd < 0)
			return false;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("No"));
	}

	if (catCharacter || (!dogCharacter->AnimalsCombined && CombinationOnlyOpen))
		return false;
	else
		return bDogCanOpen;
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
