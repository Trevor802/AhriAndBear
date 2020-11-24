// Fill out your copyright notice in the Description page of Project Settings.


#include "ABClimbZone.h"
#include "Characters/ABCatCharacter.h"
#include "CharacterInteractionComponent.h"

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

	ClimbTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABClimbZone::OnEnterCollision);
	ClimbTrigger->OnComponentEndOverlap.AddDynamic(this, &AABClimbZone::OnExitCollision);
}

void AABClimbZone::OnEnterCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp && Cast<AABCatCharacter>(OtherActor) && Cast<UCharacterInteractionComponent>(OtherComp))
	{
		AABCatCharacter* tempChara = Cast<AABCatCharacter>(OtherActor);
		tempChara->bInClimbingZone = true;
	}
}

void AABClimbZone::OnExitCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherComp && Cast<AABCatCharacter>(OtherActor) && Cast<UCharacterInteractionComponent>(OtherComp))
	{
		AABCatCharacter* tempChara = Cast<AABCatCharacter>(OtherActor);
		tempChara->bInClimbingZone = false;
	}
}

// Called every frame
void AABClimbZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

