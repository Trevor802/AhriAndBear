// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "Interactives/OccupyingInteractive.h"
#include "GameBase/Define.h"
#include "ABInteractiveObjectWater.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectWater : public AOccupyingInteractive
{
	GENERATED_BODY()
	
public:
	AABInteractiveObjectWater();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent* component) const override { return true; }
	virtual void EndInteraction(bool) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	FSurvivalData SurvivalEffect;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* CollisionShape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* BowlMesh;

};
