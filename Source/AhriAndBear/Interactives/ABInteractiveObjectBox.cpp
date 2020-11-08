// Fill out your copyright notice in the Description page of Project Settings.

#include "ABInteractiveObjectBox.h"
#include "Components/BoxComponent.h"
#include "ABAnimalCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Interactives/EventTrigger.h"

AABInteractiveObjectBox::AABInteractiveObjectBox() : Super()
{
	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionShape;

	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	//RootComponent = boxMesh;
	boxMesh->SetupAttachment(RootComponent);
	//boxMesh->SetSimulatePhysics(true);

}

void AABInteractiveObjectBox::BeginPlay()
{
	Super::BeginPlay();
	EventTrigger->EventData.TriggerEvent = EEventType::Nothing;
}

void AABInteractiveObjectBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABInteractiveObjectBox::AfterInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("Box interact"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Box interact"));
	FVector impulse = GetActorUpVector() * 20000;
	boxMesh->AddImpulse(impulse);
}

//void AABInteractiveObjectBox::OnActorEnter(AActor* OtherActor)
//{
//
//}
//
//void AABInteractiveObjectBox::OnActorExit(AActor* OtherActor)
//{
//
//}

void AABInteractiveObjectBox::AddForceAlongAxis(float value)
{
	FVector forceAdded = GetActorUpVector() * 20000;  //GetActorForwardVector() * 2000;
	boxMesh->AddForce(forceAdded);
}

void AABInteractiveObjectBox::EndInteraction()
{
	// Detach player from the box

	// Possess player 
}