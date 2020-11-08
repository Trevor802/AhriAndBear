// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "ABInteractiveObjectBox.generated.h"

class AActor;
class UStaticMeshComponent;

UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectBox : public AABInteractiveObjectBase
{
	GENERATED_BODY()
	
public:
	AABInteractiveObjectBox();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void AfterInteraction() override;
	//virtual void OnActorEnter(AActor* OtherActor);
	//virtual void OnActorExit(AActor* OtherActor);

	void AddForceAlongAxis(float value);
	void EndInteraction();	// End interaction with box and possess player back
	FVector GetMoveAxis(AActor* OtherActor);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* boxMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForceMagnitude;

private:
	bool bInteracting;
	AActor* actorInteracting;
	FVector moveAxis;
};
