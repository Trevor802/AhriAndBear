// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectWarmArea.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

AABInteractiveObjectWarmArea::AABInteractiveObjectWarmArea()
{
	CollisionShape = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionShape;

	VFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX"));
	VFX->SetupAttachment(RootComponent);
}

void AABInteractiveObjectWarmArea::OnActorEnter(AActor* OtherActor)
{

}

void AABInteractiveObjectWarmArea::OnActorExit(AActor* OtherActor)
{

}