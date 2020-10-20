// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectBase.h"
#include "ABAnimalCharacter.h"
#include "Interactive.h"
#include "VolumeInteractiveComponent.h"

// Sets default values
AABInteractiveObjectBase::AABInteractiveObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AABInteractiveObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionShape)
	{
		CollisionShape->OnComponentBeginOverlap.AddDynamic(this, &AABInteractiveObjectBase::OnEnterCollision);
		CollisionShape->OnComponentEndOverlap.AddDynamic(this, &AABInteractiveObjectBase::OnExitCollision);
	}
}

// Called every frame
void AABInteractiveObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABInteractiveObjectBase::AfterInteraction()
{
}

void AABInteractiveObjectBase::OnEnterCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AABAnimalCharacter* character = Cast<AABAnimalCharacter>(OtherActor);
	UVolumeInteractiveComponent* InteractiveComponent = FindComponentByClass<UVolumeInteractiveComponent>();
	if (character != nullptr && InteractiveComponent)
	{
		InteractiveComponent->AnimalOverlapping = character;
		switch (InteractiveComponent->EventData.TriggerEvent)
		{
		case EEventType::SaveGame:
			InteractiveComponent->SaveGame(character);
			break;
		case EEventType::LoadLevel:
			InteractiveComponent->LoadLevel(InteractiveComponent->EventData.LevelID);
			break;
		case EEventType::GainWarmth:
			InteractiveComponent->ChangeWarmthRate(character, InteractiveComponent->EventData.GainWarmthRate);
			break;
		default:
			break;
		}
	}
}

void AABInteractiveObjectBase::OnExitCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AABAnimalCharacter* character = Cast<AABAnimalCharacter>(OtherActor);
	UVolumeInteractiveComponent* InteractiveComponent = FindComponentByClass<UVolumeInteractiveComponent>();
	if (character != nullptr && InteractiveComponent)
	{
		InteractiveComponent->AnimalOverlapping = nullptr;
		switch (InteractiveComponent->EventData.TriggerEvent)
		{
		case EEventType::SaveGame:
			break;
		case EEventType::LoadLevel:
			break;
		case EEventType::GainWarmth:
			InteractiveComponent->ChangeWarmthRate(character, InteractiveComponent->OldWarmthRate);
			break;
		default:
			break;
		}
	}
}

