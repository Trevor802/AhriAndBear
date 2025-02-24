// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"

#include "Engine/World.h"
#include "Interactives/CharacterInteractionComponent.h"
#include "ABPlayerUIComponent.h"
#include "Components/InputComponent.h"
#include "UI/InteractionDurationWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/GamepadCompatibleWidget.h"

AABPlayerController::AABPlayerController()
	: Super()
{

}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InteractionWidget = CreateWidget<UInteractionDurationWidget>(this, WidgetClass);
	InteractionWidget->AddToViewport();

	auto gameMode = Cast<AAhriAndBearGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Yaha!"));
	if (gameMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Did it!"));
		gameMode->OnGameOver.AddDynamic(this, &AABPlayerController::HandleGameOver);
	}
}

void AABPlayerController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);

	//get reference to character
	AnimalCharacter = Cast<AABAnimalCharacter>(Pawn);
	AnimalCharacter->bOrientRotationToMovementSetting = false;
	//AnimalCharacter->ChangeMovementSetting();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
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
	ActionBindings.Add(InputComponent->BindAction("Pause", IE_Pressed, this, &AABPlayerController::Pause));

	// UI Input bindings
	// axis bindings
	auto& verticalUIInput = InputComponent->BindAxis("UI_SelectionChange", this, &AABPlayerController::UI_SelectionChange);
	verticalUIInput.bExecuteWhenPaused = true;
	AxisBindings.Add(verticalUIInput);

	auto& horizontalUIInput = InputComponent->BindAxis("UI_SliderChange", this, &AABPlayerController::UI_SliderChange);
	horizontalUIInput.bExecuteWhenPaused = true;
	AxisBindings.Add(horizontalUIInput);

	// button bindings
	auto& confirmInput = InputComponent->BindAction("UI_Confirm", IE_Pressed, this, &AABPlayerController::UI_Confirm);
	confirmInput.bExecuteWhenPaused = true;
	ActionBindings.Add(confirmInput);

	auto& cancelInput = InputComponent->BindAction("UI_Cancel", IE_Pressed, this, &AABPlayerController::UI_Cancel);
	cancelInput.bExecuteWhenPaused = true;
	ActionBindings.Add(cancelInput);

	auto& startInput = InputComponent->BindAction("UI_Start", IE_Pressed, this, &AABPlayerController::UI_Start);
	startInput.bExecuteWhenPaused = true;
	ActionBindings.Add(startInput);

	auto& selectInput = InputComponent->BindAction("UI_Select", IE_Pressed, this, &AABPlayerController::UI_Select);
	selectInput.bExecuteWhenPaused = true;
	ActionBindings.Add(selectInput);


	ConstantActionBindings.Add(InputComponent->BindAction("ChangeAnimal", IE_Pressed, this, &AABPlayerController::CallSwitchAnimal));
	ConstantActionBindings.Add(InputComponent->BindAction("Bark", IE_Pressed, this, &AABPlayerController::Bark));
	ConstantActionBindings.Add(InputComponent->BindAction("ESC", IE_Pressed, this, &AABPlayerController::Pause));
}

void AABPlayerController::CallMoveForward(float value)
{
	if (AnimalCharacter && value != 0.f && !AnimalCharacter->bReading)
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
	if (AnimalCharacter && value != 0.f && !AnimalCharacter->bReading)
	{
		const FRotator rotation = GetControlRotation();
		const FRotator YawRotation(0, rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AnimalCharacter->AddMovementInput(Direction, value);
	}
}

void AABPlayerController::CallTurnAtRate(float value)
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		AnimalCharacter->AddControllerYawInput(value * AnimalCharacter->baseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AABPlayerController::CallLookUpAtRate(float value)
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		AnimalCharacter->AddControllerPitchInput(value * AnimalCharacter->baseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AABPlayerController::CallTurn(float value)
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		AnimalCharacter->AddControllerYawInput(value);
	}
}

void AABPlayerController::CallLookUp(float value)
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		AnimalCharacter->AddControllerPitchInput(value);
	}
}

void AABPlayerController::CallJump()
{
	if (AnimalCharacter && AnimalCharacter->CanJump() && !AnimalCharacter->bReading)
	{
		AnimalCharacter->StartJumping();
	}
}

void AABPlayerController::CallSprint()
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
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
	if (AnimalCharacter && AnimalCharacter->bShowEndWidget)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "MenuLevel");
		return;
	}

	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		auto interactionComponent = AnimalCharacter->FindComponentByClass<UCharacterInteractionComponent>();
		interactionComponent->TryInteracting();
		return;
	}
	else if (AnimalCharacter && AnimalCharacter->bReading)
	{
		auto UIComponent = AnimalCharacter->FindComponentByClass<UABPlayerUIComponent>();
		UIComponent->RemoveNewspaperWidgetFromViewPort();
		CallStopReading();
	}
}

void AABPlayerController::CallUseAbility()
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		AnimalCharacter->UseAbility();
	}
}

void AABPlayerController::CallStopInteract()
{

}

void AABPlayerController::CallFollowing()
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		AnimalCharacter->ChangeOtherFollowingStatus();
	}
}

void AABPlayerController::CallSwitchAnimal()
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		AnimalCharacter->SwitchAnimal();
	}
}

void AABPlayerController::CallCrouch()
{
	if (AnimalCharacter && AnimalCharacter->CanCrouch() && !AnimalCharacter->bReading)
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

void AABPlayerController::CallReading()
{
	if (AnimalCharacter)
	{
		AnimalCharacter->bReading = true;
	}
}

void AABPlayerController::CallStopReading()
{
	if (AnimalCharacter)
	{
		AnimalCharacter->bReading = false;
	}
}

void AABPlayerController::Pause()
{
	if (PauseMenuWidgetClass == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pause menu widget class has not been set"));
		return;
	}
	// We currently rely on the pause menu to do this
	else if (!UGameplayStatics::IsGamePaused(GetWorld())) {
		currentMenu = CreateWidget<UGamepadCompatibleWidget>(GetWorld(), PauseMenuWidgetClass);

		if (!currentMenu) {
			return;
		}
		currentMenu->AddToViewport();
		//SetInputMode(FInputModeUIOnly());
		SetShowMouseCursor(true);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AABPlayerController::UI_SelectionChange(float value)
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) && currentMenu) {
		currentMenu->UIVerticalSelectionChanged(value);
	}
}

void AABPlayerController::UI_SliderChange(float value)
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) && currentMenu) {
		currentMenu->UIHorizontalSelectionChanged(value);
	}
}

void AABPlayerController::UI_Confirm()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) && currentMenu) {
		currentMenu->UIConfirmPressed();
	}
}

void AABPlayerController::UI_Cancel()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) && currentMenu) {
		currentMenu->UICancelPressed();
	}
}

void AABPlayerController::Bark()
{
	if (AnimalCharacter && !AnimalCharacter->bReading)
	{
		AnimalCharacter->Bark();
	}
}

void AABPlayerController::UI_Start()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) && currentMenu) {
		currentMenu->UIStartPressed();
	}
}

void AABPlayerController::UI_Select()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) && currentMenu) {
		currentMenu->UISelectPressed();
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
	Widget->SetVisibility(ESlateVisibility::Visible);
}

void AABPlayerController::RemoveWidgetFromViewPort(UUserWidget* Widget)
{
	Widget->SetVisibility(ESlateVisibility::Hidden);
	Widget->RemoveFromViewport();
}

void AABPlayerController::HandleGameOver(const FGameOverInfo& info)
{
	SetShowMouseCursor(true);
	currentMenu = CreateWidget<UGamepadCompatibleWidget>(GetWorld(), GameOverMenuClass);

	if (!currentMenu) {
		return;
	}
	currentMenu->AddToViewport();
}

