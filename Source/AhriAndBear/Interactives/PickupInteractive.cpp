// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupInteractive.h"
#include "Components/BoxComponent.h"
#include "Interactives/CharacterInteractionComponent.h"
APickupInteractive::APickupInteractive()
{
    PhysicsComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Physics Component"));
    RootComponent = PhysicsComponent;

}

void APickupInteractive::BeginPlay()
{
    Super::BeginPlay();
    PhysicsComponent->SetSimulatePhysics(true);
}

void APickupInteractive::CallMoveForward(float value)
{
    Super::CallMoveForward(value);
}

void APickupInteractive::CallMoveRight(float value)
{
    Super::CallMoveRight(value);
}

void APickupInteractive::BeginInteraction()
{
    PhysicsComponent->SetSimulatePhysics(false);
    AttachToComponent(InteractingComponent, FAttachmentTransformRules(
        EAttachmentRule::SnapToTarget, 
        true));
    SetActorRelativeLocation(OffsetAgainstComponent);
}

void APickupInteractive::EndInteraction(bool)
{
    PhysicsComponent->SetSimulatePhysics(true);
    DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
}
