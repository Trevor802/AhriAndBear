// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteractiveObjectBase.h"
#include "Interactive.h"
#include "ABAnimalCharacter.h"
#include "ABPlayerController.h"
#include "EventTrigger.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values
AABInteractiveObjectBase::AABInteractiveObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventTrigger = CreateDefaultSubobject<UEventTrigger>(TEXT("EventTrigger"));

	UIWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UIWidget1"));
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

	UIWidget->SetWorldLocation(GetActorLocation());
}

// Called every frame
void AABInteractiveObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetWidgetDistance();
	SetWidgetRotation();
	SetWidgetVisiability();
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
	if (EventTrigger)
	{
		EventTrigger->OnExitCollision(character);
	}
}

void AABInteractiveObjectBase::SetWidgetDistance()
{
	AABAnimalCharacter* player = Cast<AABAnimalCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Distance = FVector::Dist(GetActorLocation(), player->GetActorLocation()) / 100.f;
}

void AABInteractiveObjectBase::SetWidgetRotation()
{
	AABAnimalCharacter* player = Cast<AABAnimalCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	FRotator PlayerRot = FRotationMatrix::MakeFromX(player->GetActorLocation() - GetActorLocation()).Rotator();

	FVector WidgetLocation = GetActorLocation();
	FVector TargetLocation = FVector(player->GetActorLocation().X, player->GetActorLocation().Y, WidgetLocation.Z);
	FVector Dir = (TargetLocation - WidgetLocation);
	Dir.Normalize();

	UIWidget->SetWorldRotation(Dir.Rotation());
}

void AABInteractiveObjectBase::SetWidgetVisiability()
{
	if (Distance <= 1)
	{
		UIWidget->SetVisibility(false);
	}
	else
	{
		UIWidget->SetVisibility(true);
	}
}

bool AABInteractiveObjectBase::CanInteract()
{
	return bCanBeInteracted;
}

