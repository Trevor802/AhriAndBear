// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Interactive.h"
#include "GameBase/Define.h"
#include "ABAnimalCharacter.h"
#include "VolumeInteractiveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UVolumeInteractiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVolumeInteractiveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FEventData EventData;
	bool bCanInteract;
	float OldWarmthRate;
	void OnEnterCollision(AABAnimalCharacter* character);
	void OnExitCollision(AABAnimalCharacter* character);
	void Interact(AABAnimalCharacter* character);
	void SaveGame(AABAnimalCharacter*) const;
	void LoadLevel(ELevelName) const;
	void ChangeWarmthRate(AABAnimalCharacter*, float);
	void Supply(AABAnimalCharacter*, const FSurvivalData&) const;
};
