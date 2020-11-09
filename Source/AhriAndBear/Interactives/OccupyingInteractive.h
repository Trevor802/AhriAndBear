#pragma once

#include "ABInteractiveObjectBase.h"
#include "OccupyingInteractive.generated.h"

class UCharacterInteractionComponent;

UCLASS()
class AHRIANDBEAR_API AOccupyingInteractive : public AABInteractiveObjectBase
{
	GENERATED_BODY()

protected:
	virtual void AfterInteraction(bool) override;
	FTimerHandle TimerHandle;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float OccupyingDuration = 1.f;
	virtual bool TryInteracting(UCharacterInteractionComponent*) override;
};