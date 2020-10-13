// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"

AABPlayerController::AABPlayerController()
	: Super()
{

}

void AABPlayerController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);

	//get reference to character
	AnimalCharacter = Cast<AABAnimalCharacter>(Pawn);
}

void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAxis("WalkForward", this, &AABPlayerController::CallMoveForward);
	InputComponent->BindAxis("WalkRight", this, &AABPlayerController::CallMoveRight);
	InputComponent->BindAxis("Turn", this, &AABPlayerController::CallTurnAtRate);
	InputComponent->BindAxis("LookUp", this, &AABPlayerController::CallLookUpAtRate);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AABPlayerController::CallJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AABPlayerController::CallStopJump);

}

void AABPlayerController::CallMoveForward(float value)
{
	if ( AnimalCharacter && value != 0.f && AnimalCharacter->CanMove())
	{
		const FRotator rotation = GetControlRotation();
		const FRotator YawRotation(0, rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AnimalCharacter->AddMovementInput(Direction, value);
	}
}

void AABPlayerController::CallMoveRight(float value)
{
	if (AnimalCharacter && value != 0.f && AnimalCharacter->CanMove())
	{
		const FRotator rotation = GetControlRotation();
		const FRotator YawRotation(0, rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AnimalCharacter->AddMovementInput(Direction, value);
	}
}

void AABPlayerController::CallTurnAtRate(float value)
{
	if (AnimalCharacter && AnimalCharacter->CanMove())
	{
		AnimalCharacter->AddControllerYawInput(value * AnimalCharacter->baseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AABPlayerController::CallLookUpAtRate(float value)
{
	if (AnimalCharacter && AnimalCharacter->CanMove())
	{
		AnimalCharacter->AddControllerPitchInput(value * AnimalCharacter->baseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AABPlayerController::CallJump()
{
	if (AnimalCharacter->CanJump() && AnimalCharacter->CanMove())
	{
		AnimalCharacter->StartJumping();
		AnimalCharacter->Jump();
	}
}

void AABPlayerController::CallStopJump()
{
	if (AnimalCharacter)
	{
		AnimalCharacter->StopJumping();
	}
}

void AABPlayerController::CallInteract()
{
	if (AnimalCharacter && AnimalCharacter->CanInteract())
	{
		AnimalCharacter->StartInteracting();
	}
}


