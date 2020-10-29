// Fill out your copyright notice in the Description page of Project Settings.

#include "ABInteractiveObjectManholeCover.h"
#include "GameBase/Define.h"
#include "EventTrigger.h"
#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"

AABInteractiveObjectManholeCover::AABInteractiveObjectManholeCover() : Super()
{
    CollisionShape = CreateDefaultSubobject<class USphereComponent>(TEXT("CollisionSphrere"));
    RootComponent = CollisionShape;
    ManholeCoverMesh = CreateDefaultSubobject<class UStaticMeshComponent>(TEXT("Manhole Cover"));
    ManholeCoverMesh->SetupAttachment(RootComponent);
    ManholeCoverMesh->SetCollisionProfileName(TEXT("NoCollision"));
    SteamParticle = CreateDefaultSubobject<class UNiagaraComponent>(TEXT("Steam Particle"));
    SteamParticle->SetupAttachment(RootComponent);
}

void AABInteractiveObjectManholeCover::BeginPlay()
{
    Super::BeginPlay();
    EventTrigger->EventData.TriggerEvent = EEventType::GainWarmth;
    EventTrigger->EventData.GainWarmthRate = WarmthRecoveryRate;
}
