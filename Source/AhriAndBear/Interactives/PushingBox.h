// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/Interactive.h"
#include "PushingBox.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
UCLASS()
class AHRIANDBEAR_API APushingBox : public AInteractive
{
	GENERATED_BODY()
	
public:
	APushingBox();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent*) const override { return true; }
	FORCEINLINE virtual void CallSprint() override {};
	FORCEINLINE virtual void CallStopSprint() override {};

	virtual void CallMoveForward(float) override;
	virtual void CallMoveRight(float value) override {};
	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* boxMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UBoxComponent* trigger_h;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UBoxComponent* trigger_v;
};
