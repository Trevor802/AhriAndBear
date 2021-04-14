// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerUIComponent.h"

// Sets default values for this component's properties
UABPlayerUIComponent::UABPlayerUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bHintWidgetShowed = false;
	bInteractiveHintWidgetShowed = false;
	// ...
}


// Called when the game starts
void UABPlayerUIComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UABPlayerUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PlayerController = Cast<AABPlayerController>(Cast<AABAnimalCharacter>(GetOwner())->GetController());
	character = Cast<AABAnimalCharacter>(GetOwner());
	/*
	if (NewspaperWidget == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("init widget"));
		InitWidgets();
	}
	*/
	CheckHintUI();
	CheckInteractiveHintUI();
}

void UABPlayerUIComponent::AddNewspaperWidgetToViewPort()
{
	if (PlayerController)
	{
		InitNewsWidget();
		PlayerController->AddWidgetToViewPort(NewspaperWidget);
		PlayerController->CallReading();
	}
}

void UABPlayerUIComponent::RemoveNewspaperWidgetFromViewPort()
{
	if (NewspaperWidget)
	{
		NewspaperWidget->RemoveFromParent();
		NewspaperWidget = nullptr;
	}

	if (PlayerController)
	{
		PlayerController->CallStopReading();
	}
}

void UABPlayerUIComponent::InitNewsWidget()
{
	if (PlayerController)
	{
		NewspaperWidget = CreateWidget<UNewspaperWidget>(PlayerController, NewspaperWidgetClass);
	}
}

void UABPlayerUIComponent::InitHintWidget()
{
	if (PlayerController)
	{
		HintWidget = CreateWidget<UHintWidget>(PlayerController, HintWidgetClass);
	}
}

void UABPlayerUIComponent::InitInteractiveHintWidget()
{
	if (PlayerController)
	{
		InteractiveHintWidget = CreateWidget<UInteractiveHintWidget>(PlayerController, IntreactiveHintWidgetClass);
	}
}

void UABPlayerUIComponent::AddHintWidgetToViewPort()
{
	if (PlayerController)
	{
		InitHintWidget();
		PlayerController->AddWidgetToViewPort(HintWidget);
	}
}

void UABPlayerUIComponent::CheckHintUI()
{
	if (PlayerController && character)
	{
		if (character->bShowHint && !bHintWidgetShowed)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("open hint"));
			AddHintWidgetToViewPort();

			bHintWidgetShowed = true;
			HintWidget->HintString = character->HintString;
			HintWidget->ShowHint(3.0f);

			FTimerDelegate HintDelegate = FTimerDelegate::CreateUObject(this, &UABPlayerUIComponent::HideHintUI);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, HintDelegate, 5.0f, false);
		}
	}
}

void UABPlayerUIComponent::HideHintUI()
{
	if (character)
	{
		bHintWidgetShowed = false;
		HintWidget->HideHint();
		character->bShowHint = false;
	}
}

void UABPlayerUIComponent::AddInteractiveHintWidgetToViewPort()
{
	if (PlayerController)
	{
		InitInteractiveHintWidget();
		PlayerController->AddWidgetToViewPort(InteractiveHintWidget);
	}
}

void UABPlayerUIComponent::CheckInteractiveHintUI()
{
	if (PlayerController && character)
	{
		if (character->bShowInteractiveHint && !bInteractiveHintWidgetShowed)
		{
			AddInteractiveHintWidgetToViewPort();
			bInteractiveHintWidgetShowed = true;
			InteractiveHintWidget->ShowHint();
		}
		else if (!character->bShowInteractiveHint && bInteractiveHintWidgetShowed)
		{
			HideInteractiveHintUI();
			bInteractiveHintWidgetShowed = false;
		}
	}
}

void UABPlayerUIComponent::HideInteractiveHintUI()
{
	InteractiveHintWidget->HideHint();
}

