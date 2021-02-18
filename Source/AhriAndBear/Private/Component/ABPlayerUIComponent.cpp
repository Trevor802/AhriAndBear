// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerUIComponent.h"

// Sets default values for this component's properties
UABPlayerUIComponent::UABPlayerUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UABPlayerUIComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AABPlayerController>(Cast<AABAnimalCharacter>(GetOwner())->GetController());

	InitWidgets();
	
}


// Called every frame
void UABPlayerUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UABPlayerUIComponent::AddNewspaperWidgetToViewPort()
{
	if (PlayerController)
	{
		PlayerController->AddWidgetToViewPort(NewspaperWidget);
		PlayerController->CallReading();
	}
}

void UABPlayerUIComponent::RemoveNewspaperWidgetFromViewPort()
{
	NewspaperWidget->RemoveFromParent();

	if (PlayerController)
	{
		PlayerController->CallStopReading();
	}
}

void UABPlayerUIComponent::InitWidgets()
{
	if (PlayerController)
	{
		NewspaperWidget = CreateWidget<UNewspaperWidget>(PlayerController, NewspaperWidgetClass);
	}
}

