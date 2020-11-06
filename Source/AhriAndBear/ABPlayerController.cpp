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
	AnimalCharacter->bOrientRotationToMovementSetting = false;
	AnimalCharacter->ChangeMovementSetting();
}

void AABPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AnimalCharacter)
	{
		AnimalCharacter->UpdateChecking();
	}
}

void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAxis("WalkForward", this, &AABPlayerController::CallMoveForward);
	InputComponent->BindAxis("WalkRight", this, &AABPlayerController::CallMoveRight);
	InputComponent->BindAxis("TurnRate", this, &AABPlayerController::CallTurnAtRate);
	InputComponent->BindAxis("LookUpRate", this, &AABPlayerController::CallLookUpAtRate);
	InputComponent->BindAxis("Turn", this, &AABPlayerController::CallTurn);
	InputComponent->BindAxis("LookUp", this, &AABPlayerController::CallLookUp);

	InputComponent->BindAction("Catch", IE_Pressed, this, &AABPlayerController::CallInteract);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AABPlayerController::CallJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AABPlayerController::CallStopJump);
	InputComponent->BindAction("Jog", IE_Pressed, this, &AABPlayerController::CallSprint);
	InputComponent->BindAction("Jog", IE_Released, this, &AABPlayerController::CallStopSprint);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AABPlayerController::CallCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AABPlayerController::CallStopCrouch);
	InputComponent->BindAction("UseSkill", IE_Pressed, this, &AABPlayerController::CallUseAbility);
	InputComponent->BindAction("AnimalTogether", IE_Pressed, this, &AABPlayerController::CallFollowing);
	InputComponent->BindAction("ChangeAnimal", IE_Pressed, this, &AABPlayerController::CallSwitchAnimal);
	InputComponent->BindAction("ESC", IE_Pressed, this, &AABPlayerController::QuitGame);

}

void AABPlayerController::CallMoveForward(float value)
{
	if (AnimalCharacter->CanClimb() == false || AnimalCharacter->bSprinting == false) // not climbing
	{
		if (AnimalCharacter && value != 0.f && AnimalCharacter->CanMove())
		{
			const FRotator rotation = GetControlRotation();
			const FRotator YawRotation(0, rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AnimalCharacter->AddMovementInput(Direction, value);

			AnimalCharacter->bClimbing = false;
		}
	}
	else // climb up
	{
		if (AnimalCharacter && value != 0.f && AnimalCharacter->CanMove())
		{
			const FRotator rotation = GetControlRotation();
			const FRotator YawRotation(0, rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

			AnimalCharacter->AddMovementInput(Direction, value);

			AnimalCharacter->bClimbing = true;
		}
	}
}

void AABPlayerController::CallMoveRight(float value)
{
	if (AnimalCharacter->CanClimb() == false || AnimalCharacter->bSprinting == false) // not climbing
	{
		if (AnimalCharacter && value != 0.f && AnimalCharacter->CanMove())
		{
			const FRotator rotation = GetControlRotation();
			const FRotator YawRotation(0, rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AnimalCharacter->AddMovementInput(Direction, value);
		}
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

void AABPlayerController::CallTurn(float value)
{
	if (AnimalCharacter && AnimalCharacter->CanMove())
	{
		AnimalCharacter->AddControllerYawInput(value);
	}
}

void AABPlayerController::CallLookUp(float value)
{
	if (AnimalCharacter && AnimalCharacter->CanMove())
	{
		AnimalCharacter->AddControllerPitchInput(value);
	}
}

void AABPlayerController::CallJump()
{
	if (AnimalCharacter && AnimalCharacter->CanJump() && AnimalCharacter->CanMove())
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

void AABPlayerController::CallSprint()
{
	if (AnimalCharacter && AnimalCharacter->CanSprint())
	{
		AnimalCharacter->StartSprinting();
	}
}

void AABPlayerController::CallStopSprint()
{
	if (AnimalCharacter && AnimalCharacter->bSprinting == true)
	{
		AnimalCharacter->EndSprinting();
	}
}

void AABPlayerController::CallInteract()
{
	if (AnimalCharacter && AnimalCharacter->CanInteract())
	{
		AnimalCharacter->StartInteracting();
	}
}

void AABPlayerController::CallUseAbility()
{
	if (AnimalCharacter && AnimalCharacter->CanUseAbility())
	{
		AnimalCharacter->UseAbility();
	}
}

void AABPlayerController::CallFollowing()
{
	if (AnimalCharacter)
	{
		AnimalCharacter->ChangeOtherFollowingStatus();
	}
}

void AABPlayerController::CallSwitchAnimal()
{
	if (AnimalCharacter)
	{
		AnimalCharacter->SwitchAnimal();
	}
}

void AABPlayerController::CallCrouch()
{
	if (AnimalCharacter && AnimalCharacter->CanCrouch())
	{
		AnimalCharacter->StartCrouch();
	}
}

void AABPlayerController::CallStopCrouch()
{
	if (AnimalCharacter)
	{
		AnimalCharacter->EndCrouch();
	}
}

void AABPlayerController::QuitGame() 
{
	FGenericPlatformMisc::RequestExit(true);
}


