// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABScentTrail.generated.h"

class USplineComponent;
class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;
UCLASS()
class AHRIANDBEAR_API AABScentTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Property")
	int Interval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Property")
	UNiagaraSystem* TemplateSystem;

	// Sets default values for this actor's properties
	AABScentTrail();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USplineComponent* spline;

	TArray<UNiagaraComponent*> systemArray;

	void InitTrail();
	void ShowTrail();
	void HideTrail();
};
