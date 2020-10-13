// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimalCharacter.h"
#include "Engine.h"
#include "Components/InputComponent.h"

// Sets default values
AABAnimalCharacter::AABAnimalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	camera->SetupAttachment(springArm);

	InterationTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InterationTrigger"));
	InterationTrigger->SetupAttachment(RootComponent);

	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;

	bWithinRange = false;
}

// Called when the game starts or when spawned
void AABAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InterationTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABAnimalCharacter::OnInteractionOverlapBegin);
	InterationTrigger->OnComponentEndOverlap.AddDynamic(this, &AABAnimalCharacter::OnInteractionOverlapEnd);
}

// Called every frame
void AABAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABAnimalCharacter::StartJumping()
{
	bJumping = true;

	FTimerDelegate JumpTimerDelegate = FTimerDelegate::CreateUObject(this, &AABAnimalCharacter::EndJumping);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, JumpTimerDelegate, 0.5f, false);
}

void AABAnimalCharacter::EndJumping()
{
	bJumping = false;
}

void AABAnimalCharacter::StartInteracting()
{
	if (InteractiveObjectRef)
	{
		bInteracting = true;
		InteractiveObjectRef->bInteracted = true;
	
		float InteractingCooldown = 0.0f;

		switch (InteractiveObjectRef->IteractiveObjectTypes)
		{
			case(EABIteractiveObjectTypes::Food):
				InteractingCooldown = 2.0f;
			case(EABIteractiveObjectTypes::Water):
				InteractingCooldown = 1.0f;
			case(EABIteractiveObjectTypes::Gate):
				InteractingCooldown = 0.5f;
		}

		FTimerDelegate InteractionTimerDelegate = FTimerDelegate::CreateUObject(this, &AABAnimalCharacter::EndInteracting);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, InteractionTimerDelegate, InteractingCooldown, false);
	}	
}

void AABAnimalCharacter::EndInteracting()
{
	bInteracting = false;
}

bool AABAnimalCharacter::CanMove()
{
	if (bInteracting == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AABAnimalCharacter::CanInteract()
{
	if (bInteracting == true || bWithinRange == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void AABAnimalCharacter::OnInteractionOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<AABInteractiveObjectBase>(OtherActor)) 
	{
		InteractiveObjectRef = Cast<AABInteractiveObjectBase>(OtherActor);
		bWithinRange = true;
	}
}

void AABAnimalCharacter::OnInteractionOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && Cast<AABInteractiveObjectBase>(OtherActor))
	{
		InteractiveObjectRef = nullptr;
		bWithinRange = false;
	}
}
