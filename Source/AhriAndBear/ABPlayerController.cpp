// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"
#include "Engine/World.h"
#include "Interactives/CharacterInteractionComponent.h"
#include "Components/InputComponent.h"
#include "UI/InteractionDurationWidget.h"
#include "Blueprint/UserWidget.h"

AABPlayerController::AABPlayerController()
	: Super()
{

}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InteractionWidget = CreateWidget<UInteractionDurationWidget>(this, WidgetClass);
	InteractionWidget->AddToViewport();
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

	AxisBindings.Add(InputComponent->BindAxis("WalkForward", this, &AABPlayerController::CallMoveForward));
	AxisBindings.Add(InputComponent->BindAxis("WalkRight", this, &AABPlayerController::CallMoveRight));
	AxisBindings.Add(InputComponent->BindAxis("TurnRate", this, &AABPlayerController::CallTurnAtRate));
	AxisBindings.Add(InputComponent->BindAxis("Turn", this, &AABPlayerController::CallTurn));
	AxisBindings.Add(InputComponent->BindAxis("LookUp", this, &AABPlayerController::CallLookUp));
	AxisBindings.Add(InputComponent->BindAxis("LookUpRate", this, &AABPlayerController::CallLookUpAtRate));

	ActionBindings.Add(InputComponent->BindAction("Catch", IE_Pressed, this, &AABPlayerController::CallInteract));
	ActionBindings.Add(InputComponent->BindAction("Catch", IE_Released, this, &AABPlayerController::CallStopInteract));
	ActionBindings.Add(InputComponent->BindAction("Jump", IE_Pressed, this, &AABPlayerController::CallJump));
	ActionBindings.Add(InputComponent->BindAction("Sprint", IE_Pressed, this, &AABPlayerController::CallSprint));
	ActionBindings.Add(InputComponent->BindAction("Sprint", IE_Released, this, &AABPlayerController::CallStopSprint));
	ActionBindings.Add(InputComponent->BindAction("Crouch", IE_Pressed, this, &AABPlayerController::CallCrouch));
	ActionBindings.Add(InputComponent->BindAction("Crouch", IE_Released, this, &AABPlayerController::CallStopCrouch));
	ActionBindings.Add(InputComponent->BindAction("UseSkill", IE_Pressed, this, &AABPlayerController::CallUseAbility));
	ActionBindings.Add(InputComponent->BindAction("AnimalTogether", IE_Pressed, this, &AABPlayerController::CallFollowing));

	ConstantActionBindings.Add(InputComponent->BindAction("ChangeAnimal", IE_Pressed, this, &AABPlayerController::CallSwitchAnimal));
	ConstantActionBindings.Add(InputComponent->BindAction("Bark", IE_Pressed, this, &AABPlayerController::Bark));
	ConstantActionBindings.Add(InputComponent->BindAction("ESC", IE_Pressed, this, &AABPlayerController::QuitGame));
}

void AABPlayerController::CallMoveForward(float value)
{
    if (AnimalCharacter && value != 0.f)
    {
        const FRotator rotation = GetControlRotation();
        const FRotator YawRotation(0, rotation.Yaw, 0);

		FVector Direction;
		if (AnimalCharacter->bInClimbingZone && AnimalCharacter->bSprinting)
		{
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
			AnimalCharacter->bClimbing = true;
		}
		else
		{
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AnimalCharacter->bClimbing = false;
		}
		AnimalCharacter->AddMovementInput(Direction, value);
    }
	// Don't delete code below, they are for climbing
		//if (AnimalCharacter && value != 0.f)
		//{
		//	const FRotator rotation = GetControlRotation();
		//	const FRotator YawRotation(0, rotation.Yaw, 0);

		//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

		//	AnimalCharacter->AddMovementInput(Direction, value);

		//	AnimalCharacter->bClimbing = true;
		//}
}

void AABPlayerController::CallMoveRight(float value)
{
    if (AnimalCharacter && value != 0.f)
    {
        const FRotator rotation = GetControlRotation();
        const FRotator YawRotation(0, rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AnimalCharacter->AddMovementInput(Direction, value);
    }
}

void AABPlayerController::CallTurnAtRate(float value)
{
	if (AnimalCharacter)
	{
		AnimalCharacter->AddControllerYawInput(value * AnimalCharacter->baseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AABPlayerController::CallLookUpAtRate(float value)
{
	if (AnimalCharacter)
	{
		AnimalCharacter->AddControllerPitchInput(value * AnimalCharacter->baseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AABPlayerController::CallTurn(float value)
{
	if (AnimalCharacter)
	{
		AnimalCharacter->AddControllerYawInput(value);
	}
}

void AABPlayerController::CallLookUp(float value)
{
	if (AnimalCharacter)
	{
		AnimalCharacter->AddControllerPitchInput(value);
	}
}

void AABPlayerController::CallJump()
{
	if (AnimalCharacter && AnimalCharacter->CanJump())
	{
		AnimalCharacter->StartJumping();
		AnimalCharacter->Jump();
	}
}

void AABPlayerController::CallSprint()
{
	if (AnimalCharacter)
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
	if (AnimalCharacter)
	{
		auto interactionComponent = AnimalCharacter->FindComponentByClass<UCharacterInteractionComponent>();
		interactionComponent->TryInteracting();
		return;
	}
}

void AABPlayerController::CallUseAbility()
{
	if (AnimalCharacter)
	{
		AnimalCharacter->UseAbility();
	}
}

void AABPlayerController::CallStopInteract()
{

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

void AABPlayerController::Bark()
{
	if (AnimalCharacter)
	{
		AnimalCharacter->Bark();
	}
}

void AABPlayerController::QuitGame() 
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MenuLevel")));
}

void AABPlayerController::BindInput() const
{
	InputComponent->ClearActionBindings();
	InputComponent->AxisBindings.Empty();
	for (auto& a : ActionBindings)
	{
		InputComponent->AddActionBinding(a);
	}
	for (auto& a : ConstantActionBindings)
	{
		InputComponent->AddActionBinding(a);
	}
	for (auto& a : AxisBindings)
	{
		InputComponent->AxisBindings.Add(a);
	}
}

void AABPlayerController::UnbindInput() const
{
	for (auto& a : ActionBindings)
	{
		InputComponent->RemoveActionBinding(a.GetActionName(), a.KeyEvent);
	}
	for (auto& a : AxisBindings)
	{
		InputComponent->AxisBindings.RemoveAllSwap([&a](const FInputAxisBinding& x)
												   {
													   return x.AxisName == a.AxisName;
												   });
	}
}

void AABPlayerController::AddWidgetToViewPort(UUserWidget* Widget)
{
	Widget->AddToViewport();
}

void AABPlayerController::RemoveWidgetFromViewPort(UUserWidget* Widget)
{
}

