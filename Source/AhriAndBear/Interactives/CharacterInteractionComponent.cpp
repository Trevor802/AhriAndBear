// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInteractionComponent.h"
#include "ABInteractiveObjectBase.h"

// Sets default values for this component's properties
UCharacterInteractionComponent::UCharacterInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool UCharacterInteractionComponent::TryInteracting()
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors, AABInteractiveObjectBase::StaticClass());
	TArray<AABInteractiveObjectBase*> interactives;
	for (auto& a : actors)
	{
		AABInteractiveObjectBase* interact = Cast<AABInteractiveObjectBase>(a);
		interactives.Emplace(interact);
	}
	interactives = SortInteractives(interactives);
	for (auto& i : interactives)
	{
		if (i->TryInteracting(this))
		{
			return true;
		}
	}
	return false;
}

// Called when the game starts
void UCharacterInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<AABInteractiveObjectBase*> UCharacterInteractionComponent::SortInteractives(const TArray<AABInteractiveObjectBase*>& interactives) const
{
	return TArray<AABInteractiveObjectBase*>();
}

