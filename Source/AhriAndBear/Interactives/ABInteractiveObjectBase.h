// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "ABInteractiveObjectBase.generated.h"

UCLASS(Abstract)
class AHRIANDBEAR_API AABInteractiveObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABInteractiveObjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION() void OnEnterCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnExitCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex); 
	virtual void OnActorEnter(AActor* OtherActor) {};
	virtual void OnActorExit(AActor* OtherActor) {};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UShapeComponent* CollisionShape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	class UWidgetComponent* UIWidget;

	void SetWidgetDistance();
	void SetWidgetRotation();
	void SetWidgetVisiability();

	virtual void AfterInteraction(bool) {};

public:	

	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor UIColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float Distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float WidigetChangeDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FString UIText;
};