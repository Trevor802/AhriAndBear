// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInteractionComponent.h"
#include "Containers/Array.h"
#include "UI/InteractionDurationWidget.h"
#include "Interactive.h"
#include "Blueprint/UserWidget.h"
#include "ABPlayerController.h"

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
	GetOverlappingActors(actors, AInteractive::StaticClass());
	TArray<AInteractive*> interactives;
	for (auto& a : actors)
	{
		AInteractive* interact = Cast<AInteractive>(a);
		interactives.Add(interact);
	}
	SortInteractives(interactives);
	for (auto& i : interactives)
	{
		if (i->TryInteracting(this))
		{
			InteractingActor = i;
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

void UCharacterInteractionComponent::BeginInteraction(float duration)
{
	// Store the widget, in case the character gets switched off
	Widget = GET_CONTROLLER(this)->GetInteractionWidget();
	Widget->OnBeginInteraction(duration); 
}

void UCharacterInteractionComponent::EndInteraction(bool bResult)
{
	if (Widget)
	{
		Widget->OnEndInteraction(bResult);
	}
}

// Called every frame
void UCharacterInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterInteractionComponent::SortInteractives(TArray<AInteractive*>& interactives) const
{
	interactives.Sort([](const AInteractive& lhs, const AInteractive& rhs)
					  {
						  return lhs.InteractionPriority > rhs.InteractionPriority;
					  });
}

