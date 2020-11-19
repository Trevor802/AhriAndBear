// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/Interactive.h"
#include "PickupInteractive.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API APickupInteractive : public AInteractive
{
	GENERATED_BODY()
protected:
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent*) const override { return true; }
	virtual void CallMoveForward(float) override;
	virtual void CallMoveRight(float) override;
	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;

	virtual void BeginPlay() override;

public:
	APickupInteractive();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	class UBoxComponent* PhysicsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		FName SocketName;
};
