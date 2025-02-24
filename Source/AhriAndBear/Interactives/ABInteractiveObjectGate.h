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
	virtual bool CanInteract(UCharacterInteractionComponent* component) const override;
	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactive Object | Gate")
	FVector UnlockDirection = FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* CollisionShape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* GateMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* FrameMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Constraint")
	UPhysicsConstraintComponent* DoorJoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bDogCanOpen;

	UPROPERTY(Category="Interactive Object | Gate", EditAnywhere)
		bool CombinationOnlyOpen;
	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
		void OnDoorOpened(bool bResult);
	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
		void OnBeginOpen();
private:
	bool bOpened;
};
