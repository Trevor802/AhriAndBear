// Fill out your copyright notice in the Description page of Project Settings.

#include "ABRestArea.h"
#include "Components/BoxComponent.h"
#include "ABAnimalCharacter.h"

// Sets default values
AABRestArea::AABRestArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &AABRestArea::OnActorBeginOverlap);
	//Collider->OnComponentEndOverlap.AddDynamic(this )
}

// Called when the game starts or when spawned
void AABRestArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABRestArea::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto animal = Cast<AABAnimalCharacter>(OtherActor);
	if (animal == nullptr) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entered rest area"));
}