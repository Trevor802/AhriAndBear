// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactive.generated.h"

/**
 * 
 */
#define GET_CONTROLLER(x) Cast<AABPlayerController>(Cast<AABAnimalCharacter>(x->GetOwner())->GetController())
#define GET_CHARACTER(x) Cast<AABAnimalCharacter>(x->GetOwner())
class AABPlayerController;
class UCharacterInteractionComponent;
UCLASS()
class AHRIANDBEAR_API AInteractive : public AActor
{
	GENERATED_BODY()
protected:
	AInteractive();
	UCharacterInteractionComponent* InteractingComponent;
	virtual bool CanInteract(UCharacterInteractionComponent*) const PURE_VIRTUAL(AInteractive::CanInteract, return false;);

	virtual void BeginInteraction() {};
	virtual void EndInteraction(bool) {};

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
	FORCEINLINE void StopInteract() { CallStopInteract(); }
	FORCEINLINE void UseAbility() { CallUseAbility(); }
	FORCEINLINE void Following() { CallFollowing(); }
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
	virtual void CallStopInteract() {};
	virtual void CallUseAbility();
	virtual void CallFollowing();
	virtual void CallCrouch();
	virtual void CallStopCrouch();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	int InteractionPriority;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	bool bOccupyMouth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	bool bOccupyPaw;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Task")
	bool bCanTriggerTask;

	void AfterInteraction(bool);
	bool TryInteracting(UCharacterInteractionComponent*);

	virtual void BindInput(UInputComponent*) const;
	virtual void UnbindInput(UInputComponent*) const;

private:
	TArray<FInputActionBinding> ActionBindings;
	TArray<FInputAxisBinding> AxisBindings;
	class AABPlayerController* Controller;
};
