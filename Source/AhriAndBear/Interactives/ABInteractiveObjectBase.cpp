// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectBase.h"
#include "Interactive.h"
#include "ABAnimalCharacter.h"
#include "EventTrigger.h"

// Sets default values
AABInteractiveObjectBase::AABInteractiveObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventTrigger = CreateDefaultSubobject<UEventTrigger>(TEXT("EventTrigger"));
}

// Called when the game starts or when spawned
void AABInteractiveObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionShape)
	{
		CollisionShape->OnComponentBeginOverlap.AddDynamic(this, &AABInteractiveObjectBase::OnEnterCollision);
		CollisionShape->OnComponentEndOverlap.AddDynamic(this, &AABInteractiveObjectBase::OnExitCollision);
	}
}

// Called every frame
void AABInteractiveObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABInteractiveObjectBase::OnEnterCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnActorEnter(OtherActor);
	AABAnimalCharacter* character = Cast<AABAnimalCharacter>(OtherActor);
	OverlappingAnimal = character;
	if (EventTrigger)
	{
		EventTrigger->OnEnterCollision(character);
	}
}

void AABInteractiveObjectBase::OnExitCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnActorExit(OtherActor);
	AABAnimalCharacter* character = Cast<AABAnimalCharacter>(OtherActor);
	OverlappingAnimal = nullptr;
	if (InteractionDelay)
	{
		EventTrigger->OnExitCollision(character);
	}
}

