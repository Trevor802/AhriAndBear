// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/Interactive.h"
#include "PushingBox.generated.h"

#define RETURN_IF_NULL(x) if(!x) return;

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
	
	class USceneComponent* Root;

	virtual void CallMoveForward(float) override;
	virtual void CallMoveRight(float value) override {};
	virtual void CallTurn(float value)override {};
	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;

	void TogglePushing(bool);
	void UpdateBox();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* boxMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UBoxComponent* trigger_h;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UBoxComponent* trigger_v;
};
