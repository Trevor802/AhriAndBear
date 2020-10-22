// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "ABInteractiveObjectManholeCover.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectManholeCover : public AABInteractiveObjectBase
{
	GENERATED_BODY()
	
public:
	AABInteractiveObjectManholeCover();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
	class UNiagaraComponent* SteamParticle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* ManholeCoverMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	float WarmthRecoveryRate;
};
