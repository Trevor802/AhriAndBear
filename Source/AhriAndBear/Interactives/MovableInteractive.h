// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "MovableInteractive.generated.h"

/**
 * 
 */
class AABPlayerController;
UCLASS()
class AHRIANDBEAR_API AMovableInteractive : public AABInteractiveObjectBase
{
	GENERATED_BODY()
protected:
	AMovableInteractive();
	virtual void AfterInteraction(bool) override;
	virtual bool TryInteracting(UCharacterInteractionComponent*) override;
	virtual void BindInput(UInputComponent*) const;
	virtual void UnbindInput(UInputComponent*) const;

	FORCEINLINE void MoveForward(float value) { CallMoveForward(value); }
	FORCEINLINE void MoveRight(float value) { CallMoveRight(value); }
	FORCEINLINE void Turn(float value) { CallTurn(value); }
	FORCEINLINE void LookUp(float value) { CallLookUp(value); }
	FORCEINLINE void TurnAtRate(float value) { CallTurnAtRate(value); }
	FORCEINLINE void LookUpAtRate(float value) { CallLookUpAtRate(value); }
	FORCEINLINE void Jump() { CallJump(); }
	FORCEINLINE void Sprint() { CallSprint(); }
	FORCEINLINE void StopSprint() { CallStopSprint(); }
	FORCEINLINE void Interact() { CallInteract(); }
	FORCEINLINE void UseAbility() { CallUseAbility(); }
	FORCEINLINE void Following() { CallFollowing(); }
	FORCEINLINE void SwitchAnimal() { CallSwitchAnimal(); }
	FORCEINLINE void Crouch() { CallCrouch(); }
	FORCEINLINE void StopCrouch() { CallStopCrouch(); }

	/// override the functions below to block them from passing into the character
	virtual void CallMoveForward(float value);
	virtual void CallMoveRight(float value);
	virtual void CallTurn(float value);
	virtual void CallLookUp(float value);
	virtual void CallTurnAtRate(float value);
	virtual void CallLookUpAtRate(float value);
	virtual void CallJump();
	virtual void CallSprint();
	virtual void CallStopSprint();
	virtual void CallInteract();
	virtual void CallUseAbility();
	virtual void CallFollowing();
	virtual void CallSwitchAnimal();
	virtual void CallCrouch();
	virtual void CallStopCrouch();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	bool bOccupyMouth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	bool bOccupyPaw;

private:
	TArray<FInputActionBinding> ActionBindings;
	TArray<FInputAxisBinding> AxisBindings;
	class AABPlayerController* Controller;
};
