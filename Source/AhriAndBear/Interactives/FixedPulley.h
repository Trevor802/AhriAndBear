// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "FixedPulley.generated.h"

class UCableComponent;
UCLASS()
class AHRIANDBEAR_API AFixedPulley : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFixedPulley();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class USceneComponent* Root;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UCableComponent* CableStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UCableComponent* CableEnd;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class USphereComponent* Start;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class USphereComponent* End;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	float TotalLength = 200.0f;

};
