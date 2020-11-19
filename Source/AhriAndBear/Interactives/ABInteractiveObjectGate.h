// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "Interactives/OccupyingInteractive.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "ABInteractiveObjectGate.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectGate : public AOccupyingInteractive
{
	GENERATED_BODY()
	
public:
	AABInteractiveObjectGate();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent* component) const override { return !bOpened; }
	virtual void EndInteraction(bool) override;
	//FORCEINLINE virtual bool CanInteract() override { return true; }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* CollisionShape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* GateMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* GateHinge;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* FrameMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Constraint")
	UPhysicsConstraintComponent* DoorJoint;

private:
	bool bOpened;
};
