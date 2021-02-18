// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/Interactive.h"
#include "Characters/ABDogCharacter.h"
#include "Interactives/CharacterInteractionComponent.h"

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
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent* interactingComponent) const override { 
		return Cast<AABDogCharacter>(GET_CHARACTER(interactingComponent)) != nullptr;
	}
	FORCEINLINE virtual void CallSprint() override {};
	FORCEINLINE virtual void CallStopSprint() override {};
	
	class USceneComponent* Root;

	virtual void CallMoveForward(float) override;
	virtual void CallMoveRight(float value) override ;
	virtual void CallTurn(float value)override {};
	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;

	void UpdateBox();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* boxMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	UBoxComponent* collider;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UBoxComponent* trigger_h;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UBoxComponent* trigger_v;*/

private:
	/*UFUNCTION()
	void h_OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void h_OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void v_OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void v_OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);*/
	void LockMeshLocation();

	bool horizontal;
	bool verticle;
};
