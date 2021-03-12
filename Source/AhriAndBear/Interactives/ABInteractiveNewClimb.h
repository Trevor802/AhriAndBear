// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/OccupyingInteractive.h"
#include "Interactives/Interactive.h"
#include "ABInteractiveNewClimb.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveNewClimb : public AInteractive
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		TArray<class AActor*> ClimbPoints;
/*
public:
	// Sets default values for this actor's properties
	AABInteractiveNewClimb();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;

	virtual void CallMoveForward(float) override {};
	virtual void CallMoveRight(float value) override {};
	virtual void CallTurn(float value)override {};
	*/
};
