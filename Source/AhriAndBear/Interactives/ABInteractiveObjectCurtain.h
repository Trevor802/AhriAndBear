// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactives/OccupyingInteractive.h"
#include "ABInteractiveObjectCurtain.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectCurtain : public AOccupyingInteractive
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AABInteractiveObjectCurtain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent* component) const override { return !bOpened; }
	virtual void EndInteraction(bool) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void OpenCurtain();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* CollisionShape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* CurtainMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class USplineComponent* Spline;
	UPROPERTY(EditAnywhere, Category = "Controller")
		float TotalPathTime = 2.f;

private:
	bool bOpened;
	float StartTime;
	
};
