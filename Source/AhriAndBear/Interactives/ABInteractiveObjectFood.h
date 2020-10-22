// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "GameBase/Define.h"
#include "ABInteractiveObjectFood.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectFood : public AABInteractiveObjectBase
{
	GENERATED_BODY()
	
public:
	AABInteractiveObjectFood();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//FORCEINLINE virtual bool CanInteract() override { return true; }
	virtual void AfterInteraction() override;
	
public:

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
