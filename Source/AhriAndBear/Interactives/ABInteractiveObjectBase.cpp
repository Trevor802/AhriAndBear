// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectBase.h"

// Sets default values
AABInteractiveObjectBase::AABInteractiveObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bInteracted = false;
}

// Called when the game starts or when spawned
void AABInteractiveObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABInteractiveObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

