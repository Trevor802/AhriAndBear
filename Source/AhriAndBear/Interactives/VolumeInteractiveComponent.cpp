// Fill out your copyright notice in the Description page of Project Settings.


#include "VolumeInteractiveComponent.h"
#include "AABSurvivalComponent.h"
#include "../GameBase/ABGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UVolumeInteractiveComponent::UVolumeInteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UVolumeInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UVolumeInteractiveComponent::OnEnterCollision(AABAnimalCharacter* character)
{
	if (character != nullptr)
	{
		switch (EventData.TriggerEvent)
		{
		case EEventType::SaveGame:
			SaveGame(character);
			break;
		case EEventType::LoadLevel:
			LoadLevel(EventData.LevelID);
			break;
		case EEventType::GainWarmth:
			ChangeWarmthRate(character, EventData.GainWarmthRate);
			break;
		default:
			break;
		}
	}
}

void UVolumeInteractiveComponent::SaveGame(AABAnimalCharacter* character) const
{
	UAABSurvivalComponent* survivalComp = character->GetOwner()->FindComponentByClass<UAABSurvivalComponent>();
	if (survivalComp != nullptr)
	{
		UABGameInstance* gameInstance = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (gameInstance != nullptr)
		{
			gameInstance->Add(character->AnimalType, FAnimalData{ character->GetActorTransform(), survivalComp->GetSurvivalData() });
		}
	}
}

void UVolumeInteractiveComponent::LoadLevel(ELevelName levelID) const
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ELevelName"), true);
	FString str = "";
	if (enumPtr)
	{
		str = enumPtr->GetNameStringByIndex((int32)levelID);
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName(*str));
}

void UVolumeInteractiveComponent::Supply(AABAnimalCharacter* character, const FSurvivalData& value) const
{
	UAABSurvivalComponent* survivalComp = character->GetOwner()->FindComponentByClass<UAABSurvivalComponent>();
	if (survivalComp != nullptr)
	{
		survivalComp->AddSurvivalData(value);
	}
}

void UVolumeInteractiveComponent::ChangeWarmthRate(AABAnimalCharacter* character, float value)
{
	UAABSurvivalComponent* survivalComp = character->GetOwner()->FindComponentByClass<UAABSurvivalComponent>();
	if (survivalComp != nullptr)
	{
		OldWarmthRate = survivalComp->WarmthChangeRate;
		survivalComp->WarmthChangeRate = value;
	}
}

void UVolumeInteractiveComponent::OnExitCollision(AABAnimalCharacter* character)
{
	if (character != nullptr)
	{
		switch (EventData.TriggerEvent)
		{
		case EEventType::SaveGame:
			break;
		case EEventType::LoadLevel:
			break;
		case EEventType::GainWarmth:
			ChangeWarmthRate(character, OldWarmthRate);
			break;
		default:
			break;
		}
	}
}

// Called every frame
void UVolumeInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVolumeInteractiveComponent::Interact(AABAnimalCharacter* character)
{
	if (character != nullptr)
	{
		switch (EventData.TriggerEvent)
		{
		case EEventType::Supply:
			Supply(character, EventData.SurvivalData);
			break;
		default:
			break;
		}
	}
}
