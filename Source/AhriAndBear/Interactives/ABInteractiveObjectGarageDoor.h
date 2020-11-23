// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactives/OccupyingInteractive.h"
#include "ABInteractiveObjectGarageDoor.generated.h"

UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectGarageDoor : public AOccupyingInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABInteractiveObjectGarageDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent* component) const override { return !bOpened; }
	virtual void EndInteraction(bool) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void OpenDoor();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* CollisionShape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* DoorMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* ButtonMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class USplineComponent* Spline;
	UPROPERTY(EditAnywhere, Category = "Controller")
		float TotalPathTime = 4.f;

private:
	bool bOpened;
	float StartTime;

};
