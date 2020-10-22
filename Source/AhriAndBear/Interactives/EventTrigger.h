// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Interactive.h"
#include "GameBase/Define.h"
#include "ABAnimalCharacter.h"
#include "EventTrigger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UEventTrigger : public UActorComponent
{
	GENERATED_BODY()

public:		
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	FEventData EventData;
	float OldWarmthRate;
	void OnEnterCollision(AABAnimalCharacter* character);
	void OnExitCollision(AABAnimalCharacter* character);
	void Interact(AABAnimalCharacter* character);
	void SaveGame(AABAnimalCharacter*) const;
	void LoadLevel(ELevelName) const;
	void ChangeWarmthRate(AABAnimalCharacter*, float);
	void Supply(AABAnimalCharacter*, const FSurvivalData&) const;
};
