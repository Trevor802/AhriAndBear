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
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &AABRestArea::OnActorBeginOverlap);
	//Collider->OnComponentEndOverlap.AddDynamic(this )
	OnActorBeginOverlap.AddDynamic(this, &AABRestArea::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AABRestArea::EndOverlap);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetGenerateOverlapEvents(true);

	ChangeRates.Hunger = 1;
	ChangeRates.Thirst = 1;
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

	OriginalChangeRates.Hunger = animal->SurvivalComponent->Hunger.RateOfChange;
	OriginalChangeRates.Thirst = animal->SurvivalComponent->Thirst.RateOfChange;

	UABSurvivalStatFunctions::SetRateOfChange(animal->SurvivalComponent->Hunger, ChangeRates.Hunger);
	UABSurvivalStatFunctions::SetRateOfChange(animal->SurvivalComponent->Thirst, ChangeRates.Thirst);
}

void AABRestArea::EndOverlap(AActor* self, AActor* otherActor) {
	auto animal = Cast<AABAnimalCharacter>(otherActor);
	if (animal == nullptr) return;

	UABSurvivalStatFunctions::SetRateOfChange(animal->SurvivalComponent->Hunger, OriginalChangeRates.Hunger);
	UABSurvivalStatFunctions::SetRateOfChange(animal->SurvivalComponent->Thirst, OriginalChangeRates.Thirst);
}