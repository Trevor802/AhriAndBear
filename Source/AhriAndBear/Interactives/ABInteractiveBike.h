// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/Interactive.h"
#include "Interactives/OccupyingInteractive.h"
#include "Interactives/CharacterInteractionComponent.h"
#include "ABInteractiveBike.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveBike : public AInteractive
{
	GENERATED_BODY()
	
public:
	AABInteractiveBike();

private:
	void MoveBike(float DeltaTime);
	void IncrementPathIndex(FVector BikeLocation, FVector TargetLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;
	virtual bool CanInteract(UCharacterInteractionComponent* interactingComponent) const override;
	virtual void CallInteract()override;

	virtual void CallMoveForward(float) override {};
	virtual void CallMoveRight(float value) override {};
	virtual void CallTurn(float value)override {};

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* BikeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		TArray<class AActor*> BikePathPoints;

private:
	bool bMoving;
	bool bCanMove;
	int PathIndex;
	float BikeSpeed;
};
