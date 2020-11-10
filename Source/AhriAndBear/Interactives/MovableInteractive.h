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
	//TArray<FInputActionBinding> ActionBindings;
	//TArray<FInputAxisBinding> AxisBindings;
	FORCEINLINE virtual void CallMoveForward(float value){};
	FORCEINLINE virtual void CallMoveRight(float value){};
	FORCEINLINE virtual void CallTurn(float value){};
	FORCEINLINE virtual void CallLookUp(float value){};
	FORCEINLINE virtual void CallTurnAtRate(float value){};
	FORCEINLINE virtual void CallLookUpAtRate(float value){};
	FORCEINLINE virtual void CallJump(){};
	FORCEINLINE virtual void CallSprint(){};
	FORCEINLINE virtual void CallStopSprint(){};
	FORCEINLINE virtual void CallInteract(){};
	FORCEINLINE virtual void CallStopInteract(){};
	FORCEINLINE virtual void CallUseAbility(){};
	FORCEINLINE virtual void CallFollowing(){};
	FORCEINLINE virtual void CallSwitchAnimal(){};
	FORCEINLINE virtual void CallCrouch(){};
	FORCEINLINE virtual void CallStopCrouch(){};

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	bool bOccupyMouth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	bool bOccupyPaw;

private:
	TArray<FInputActionBinding*> ActionBindings;
	TArray<FInputAxisBinding*> AxisBindings;
	class AABPlayerController* Controller;
};
