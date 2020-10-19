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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVolumeInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();
	if (CollisionShape)
	{
		CollisionShape->OnComponentBeginOverlap.AddDynamic(this, &UVolumeInteractiveComponent::OnEnterCollision);
		CollisionShape->OnComponentEndOverlap.AddDynamic(this, &UVolumeInteractiveComponent::OnExitCollision);
	}
}

void UVolumeInteractiveComponent::OnEnterCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AABAnimalCharacter* character = Cast<AABAnimalCharacter>(OtherActor);
	if (character != nullptr)
	{
		AnimalOverlapping = character;
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

void UVolumeInteractiveComponent::Supply(const FSurvivalData& value)
{
	check(AnimalOverlapping);
	UAABSurvivalComponent* survivalComp = AnimalOverlapping->GetOwner()->FindComponentByClass<UAABSurvivalComponent>();
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

void UVolumeInteractiveComponent::OnExitCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AABAnimalCharacter* character = Cast<AABAnimalCharacter>(OtherActor);
	if (character != nullptr)
	{
		AnimalOverlapping = nullptr;
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

void UVolumeInteractiveComponent::Interact()
{
	if (AnimalOverlapping != nullptr)
	{
		switch (EventData.TriggerEvent)
		{
		case EEventType::Supply:
			Supply(EventData.SurvivalData);
			break;
		default:
			break;
		}
	}
}
