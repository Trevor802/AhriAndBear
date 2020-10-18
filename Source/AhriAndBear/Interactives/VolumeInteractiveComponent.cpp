// Fill out your copyright notice in the Description page of Project Settings.


#include "VolumeInteractiveComponent.h"

// Sets default values for this component's properties
UVolumeInteractiveComponent::UVolumeInteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVolumeInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();
	CollisionShape->OnComponentBeginOverlap.AddDynamic(this, &UVolumeInteractiveComponent::OnEnterCollision);
	CollisionShape->OnComponentEndOverlap.AddDynamic(this, &UVolumeInteractiveComponent::OnExitCollision);
}

// Called every frame
void UVolumeInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool IInteractive::CanInteractive()
{
	return false;
}

void IInteractive::Interact()
{
}
