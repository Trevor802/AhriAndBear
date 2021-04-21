// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABAnimalCharacter.h"
#include "AhriAndBearGameModeBase.h"
#include "ABPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AABPlayerController();

	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* Pawn) override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void CallMoveForward(float value);
	void CallMoveRight(float value);
	void CallTurn(float value);
	void CallLookUp(float value);
	void CallTurnAtRate(float value);
	void CallLookUpAtRate(float value);
	void CallJump();
	void CallSprint();
	void CallStopSprint();
	void CallInteract();
	void CallStopInteract();
	void CallUseAbility();
	void CallFollowing();
	void CallSwitchAnimal();
	void CallCrouch();
	void CallStopCrouch();
	void CallReading();
	void CallStopReading();
	void Pause();

	/**
	* Passes this input event over to a GamepadCompatibleWidget.
	*/
	void UI_SelectionChange(float value);
	/**
	* Passes this input event over to a GamepadCompatibleWidget.
	*/
	void UI_SliderChange(float value);

	/**
	* Passes this input event over to a GamepadCompatibleWidget.
	*/
	void UI_Confirm();

	/**
	* Passes this input event over to a GamepadCompatibleWidget.
	*/
	void UI_Cancel();

	/**
	* Passes this input event over to a GamepadCompatibleWidget.
	*/
	void UI_Start();

	/**
	* Passes this input event over to a GamepadCompatibleWidget.
	*/
	void UI_Select();

	void QuitGame();
	void Bark();

	AABAnimalCharacter* AnimalCharacter;
	void BindInput() const;
	void UnbindInput() const;

	void AddWidgetToViewPort(UUserWidget* Widget);
	void RemoveWidgetFromViewPort(UUserWidget* Widget);

	FORCEINLINE class UInteractionDurationWidget* GetInteractionWidget() const{ return InteractionWidget; }
protected:
	// TODO: Improve this
	TArray<FInputActionBinding> ActionBindings;
	TArray<FInputActionBinding> ConstantActionBindings;
	TArray<FInputAxisBinding> AxisBindings;

	// Naive implementation, TODO: Move all UIs to a UI Manager class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UInteractionDurationWidget> WidgetClass;
	
	// This is the class of the pause menu widget shown while paused.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UGamepadCompatibleWidget> PauseMenuWidgetClass;

	// The class of game over menu that shows during game over.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UGamepadCompatibleWidget> GameOverMenuClass;

	// The current menu.
	UGamepadCompatibleWidget* currentMenu;

	class UInteractionDurationWidget* InteractionWidget;

private:
	UFUNCTION()
	void HandleGameOver(const FGameOverInfo& info);
};
