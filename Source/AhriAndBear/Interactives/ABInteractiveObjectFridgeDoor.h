// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/OccupyingInteractive.h"
#include "ABInteractiveObjectFridgeDoor.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectFridgeDoor : public AOccupyingInteractive
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AABInteractiveObjectFridgeDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool CanInteract(UCharacterInteractionComponent* interactingComponent) const override;
	virtual void EndInteraction(bool) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void OpenDoor();
	void StopRotation();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* CollisionShape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactive Object | Gate")
		FVector UnlockDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float RotationTimeLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float RotationRate;

private:
	bool bOpened;
	bool bOpening;
	float AngleAxis;
};
