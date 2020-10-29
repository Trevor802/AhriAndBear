// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "ABInteractiveObjectWarmArea.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectWarmArea : public AABInteractiveObjectBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Property")
	UNiagaraSystem* TemplateSystem;

	AABInteractiveObjectWarmArea();

	virtual void OnActorEnter(AActor* OtherActor) override;
	virtual void OnActorExit(AActor* OtherActor) override;

private:
	UNiagaraComponent* VFX;
};
