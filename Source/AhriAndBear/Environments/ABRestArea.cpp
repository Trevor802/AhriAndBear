// Fill out your copyright notice in the Description page of Project Settings.

#include "ABRestArea.h"
#include "Components/BoxComponent.h"
#include "ABSurvivalStats.h"
#include "AABSurvivalComponent.h"
#include "ABAnimalCharacter.h"

// Sets default values
AABRestArea::AABRestArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Volume"));
	OnActorBeginOverlap.AddDynamic(this, &AABRestArea::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AABRestArea::EndOverlap);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetGenerateOverlapEvents(true);

	ChangeRates.Hunger = 1;
	ChangeRates.Thirst = 1;

	// This should trump nearly every other stat modifier
	priority = 99;
}

// Called when the game starts or when spawned
void AABRestArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABRestArea::BeginOverlap(AActor* self, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entered rest area"));

	auto animal = Cast<AABAnimalCharacter>(OtherActor);
	if (animal == nullptr) return;

	animal->SurvivalComponent->AddModifier(this);
}

void AABRestArea::EndOverlap(AActor* self, AActor* otherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap over"));
	auto animal = Cast<AABAnimalCharacter>(otherActor);
	if (animal == nullptr) return;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Removing"));
	animal->SurvivalComponent->RemoveModifier(this);
}

float AABRestArea::GetHungerRateModifier(UAABSurvivalComponent* mainComp, float defaultHungerDelta, float currentDelta)
{
	return ChangeRates.Hunger;
}

float AABRestArea::GetThirstRateModifier(UAABSurvivalComponent* mainComp, float defaultThirstDelta, float currentDelta)
{
	return ChangeRates.Thirst;
}


