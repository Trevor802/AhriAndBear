// Fill out your copyright notice in the Description page of Project Settings.

#include "ABInteractiveObjectPlaySound.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

AABInteractiveObjectPlaySound::AABInteractiveObjectPlaySound()
{
    CollisionShape = CreateDefaultSubobject<class UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionShape;
    Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
    Sound->SetupAttachment(RootComponent);
    Sound->bAutoActivate = false;
}

void AABInteractiveObjectPlaySound::OnActorEnter(AActor*)
{
    Sound->Play();
}

void AABInteractiveObjectPlaySound::OnActorExit(AActor*)
{
    Sound->Play();
}
