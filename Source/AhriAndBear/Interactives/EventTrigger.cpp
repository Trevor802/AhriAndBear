// Fill out your copyright notice in the Description page of Project Settings.


#include "EventTrigger.h"
#include "AABSurvivalComponent.h"
#include "../GameBase/ABGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UEventTrigger::OnEnterCollision(AABAnimalCharacter* character)
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

void UEventTrigger::SaveGame(AABAnimalCharacter* character) const
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

void UEventTrigger::LoadLevel(ELevelName levelID) const
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ELevelName"), true);
	FString str = "";
	if (enumPtr)
	{
		str = enumPtr->GetNameStringByIndex((int32)levelID);
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName(*str));
}

void UEventTrigger::Supply(AABAnimalCharacter* character, const FSurvivalData& value) const
{
	UAABSurvivalComponent* survivalComp = character->GetOwner()->FindComponentByClass<UAABSurvivalComponent>();
	if (survivalComp != nullptr)
	{
		survivalComp->AddSurvivalData(value);
	}
}

void UEventTrigger::ChangeWarmthRate(AABAnimalCharacter* character, float value)
{
	UAABSurvivalComponent* survivalComp = character->GetOwner()->FindComponentByClass<UAABSurvivalComponent>();
	if (survivalComp != nullptr)
	{
		OldWarmthRate = survivalComp->WarmthChangeRate;
		survivalComp->WarmthChangeRate = value;
	}
}

void UEventTrigger::OnExitCollision(AABAnimalCharacter* character)
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

void UEventTrigger::Interact(AABAnimalCharacter* character)
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
