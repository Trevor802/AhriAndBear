// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABAnimalCharacter.h"
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

	void CallMoveForward(float value);
	void CallMoveRight(float value);
	void CallTurn(float value);
	void CallLookUp(float value);
	void CallTurnAtRate(float value);
	void CallLookUpAtRate(float value);
	void CallJump();
	void CallStopJump();
	void CallSprint();
	void CallStopSprint();
	void CallInteract();
	void CallStopInteract();
	void CallUseAbility();
	void CallFollowing();
	void CallSwitchAnimal();
	void CallCrouch();
	void CallStopCrouch();
	
	void QuitGame();

	AABAnimalCharacter* AnimalCharacter;
	void BindInput() const;
	void UnbindInput() const;
protected:
	TArray<FInputActionBinding> ActionBindings;
	TArray<FInputAxisBinding> AxisBindings;
};
