#pragma once

#include "MovableInteractive.h"
#include "OccupyingInteractive.generated.h"

class UCharacterInteractionComponent;

UCLASS()
class AHRIANDBEAR_API AOccupyingInteractive : public AMovableInteractive
{
	GENERATED_BODY()

protected:
	FTimerHandle TimerHandle;
	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;
	virtual void CallStopInteract() override;

	// Block the inputs below
	virtual void CallMoveForward(float) override {};
	virtual void CallMoveRight(float) override {};
	virtual void CallTurn(float) override {};
	virtual void CallLookUp(float) override {};
	virtual void CallTurnAtRate(float) override {};
	virtual void CallLookUpAtRate(float) override {};
	virtual void CallJump() {};
	virtual void CallSprint() {};
	virtual void CallStopSprint() {};
	virtual void CallUseAbility() {};
	virtual void CallFollowing() {};
	virtual void CallSwitchAnimal() {};
	virtual void CallCrouch() {};
	virtual void CallStopCrouch() {};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float OccupyingDuration = 1.f;
};