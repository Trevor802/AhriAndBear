// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactives/ABInteractiveNewClimb.h"
#include "ABAnimalCharacter.h"
#include "ABPlayerController.h"
#include "Characters/ABCatCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AABInteractiveNewClimb::AABInteractiveNewClimb()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Climb Trigger"));
	RootComponent = Collider;

	ClimbPointsIndex = 0;
	ClimbSpeed = 500.0f;
	bClimbing = false;
}

void AABInteractiveNewClimb::BeginPlay()
{
	Super::BeginPlay();
}

void AABInteractiveNewClimb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bClimbing == true)
	{
		ClimbToNext(DeltaTime);
	}
}

void AABInteractiveNewClimb::BeginInteraction()
{
	bClimbing = true;

	auto character = GET_CHARACTER(InteractingComponent);
	AABCatCharacter* catCharacter = Cast<AABCatCharacter>(character);
	if (catCharacter)
	{
		//catCharacter->GetCharacterMovement()->StopActiveMovement(); 
		//catCharacter->GetCharacterMovement()->StopMovementImmediately();
		/*
		if (catCharacter->GetCharacterMovement()->Velocity != FVector::ZeroVector)
		{
			AfterInteraction(true);
			return;
		}
		*/
		catCharacter->bClimbing = true;
		CatInteractionComponent = InteractingComponent;
	}
}

void AABInteractiveNewClimb::EndInteraction(bool)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Reset"));
	ResetClimb();
}

bool AABInteractiveNewClimb::CanInteract(UCharacterInteractionComponent* interactingComponent) const {
	if (!Super::CanInteract(interactingComponent)) {
		return false;
	}

	auto character = GET_CHARACTER(interactingComponent);
	AABCatCharacter* catCharacter = Cast<AABCatCharacter>(character);
	if (!catCharacter)
	{
		return false;
	}
	else
	{
		if (catCharacter->GetCharacterMovement()->Velocity != FVector::ZeroVector)
		{
			return false;
		}
	}

	return true;
}

void AABInteractiveNewClimb::CallInteract()
{
	/*
	if (bClimbing == true)
	{
		return;
	}

	if (ClimbPointsIndex < ClimbPoints.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("To Next"));
		bClimbing = true;
	}
	*/
	/*
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("End"));
		AfterInteraction(true);
	}
	*/
}

void AABInteractiveNewClimb::ClimbToNext(float DeltaTime)
{
	if (ClimbPoints.Num() != 0 && CatInteractionComponent)
	{
		auto character = GET_CHARACTER(CatInteractionComponent);
		AABCatCharacter* catCharacter = Cast<AABCatCharacter>(character);
		if (catCharacter)
		{
			/*
			if (catCharacter->GetCharacterMovement()->Velocity != FVector::ZeroVector)
			{
				return;
			}
			*/
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Climbing"));

			FVector CurrentPosition = FMath::VInterpConstantTo(catCharacter->GetActorLocation(), ClimbPoints[ClimbPointsIndex]->GetActorLocation(), DeltaTime, ClimbSpeed);
			catCharacter->SetActorLocation(CurrentPosition);
			IncrementClimbIndex(catCharacter->GetActorLocation(), ClimbPoints[ClimbPointsIndex]->GetActorLocation());
		}
	}
}

void AABInteractiveNewClimb::IncrementClimbIndex(FVector CharacterLocation, FVector TargetLocation)
{
	if (FVector::Dist(CharacterLocation, TargetLocation) <= 0.1f)
	{
		ClimbPointsIndex++;
		//bClimbing = false;

		if (ClimbPointsIndex >= ClimbPoints.Num())
		{
			AfterInteraction(true);
		}
	}
}

void AABInteractiveNewClimb::ResetClimb()
{
	ClimbPointsIndex = 0;
	bClimbing = false;

	if (CatInteractionComponent)
	{
		auto character = GET_CHARACTER(CatInteractionComponent);
		AABCatCharacter* catCharacter = Cast<AABCatCharacter>(character);
		if (catCharacter)
		{
			catCharacter->bClimbing = false;
			CatInteractionComponent = nullptr;
		}
	}
	
}
