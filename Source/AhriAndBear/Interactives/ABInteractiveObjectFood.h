// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/OccupyingInteractive.h"
#include "GameBase/Define.h"
#include "ABInteractiveObjectFood.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectFood : public AOccupyingInteractive
{
	GENERATED_BODY()
	
public:
	AABInteractiveObjectFood();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent* component) const override { return FoodArray.Num() > 0; }
	virtual void EndInteraction(bool) override;

	void TempGymRespawn();
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UBoxComponent* CollisionShape;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* FoodMesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* FoodMesh2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* FoodMesh3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	FSurvivalData SurvivalEffect;

private:
	TArray<UStaticMeshComponent*> FoodArray;

};
