// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "ABInteractiveObjectBox.generated.h"

class AActor;
class UStaticMeshComponent;

UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectBox : public AABInteractiveObjectBase
{
	GENERATED_BODY()
	
public:
	AABInteractiveObjectBox();
	virtual void Tick(float DeltaTime) override;
	virtual void OnActorEnter(AActor* OtherActor);
	virtual void OnActorExit(AActor* OtherActor);

public:
	UStaticMeshComponent* boxMesh;

private:
	bool bInteracting;
};
