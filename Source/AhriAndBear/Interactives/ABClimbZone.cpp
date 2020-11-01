// Fill out your copyright notice in the Description page of Project Settings.


#include "ABClimbZone.h"

// Sets default values
AABClimbZone::AABClimbZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClimbTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ClimbTrigger"));
	ClimbTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AABClimbZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABClimbZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

