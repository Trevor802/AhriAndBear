// Fill out your copyright notice in the Description page of Project Settings.
#include "ABTaskTrigger.h"
#include "ABAnimalCharacter.h"
#include "AhriAndBearGameModeBase.h"

// Sets default values
AABTaskTrigger::AABTaskTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AABTaskTrigger::OnCharacterOverlapBegin);
}

// Called when the game starts or when spawned
void AABTaskTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABTaskTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABTaskTrigger::OnCharacterOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<AABAnimalCharacter>(OtherActor))
	{
		AAhriAndBearGameModeBase* GameMode = (AAhriAndBearGameModeBase*)GetWorld()->GetAuthGameMode();
		GameMode->ToNextTask();
		Destroy();
	}
}

