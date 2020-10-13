// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ABInteractiveObjectBase.generated.h"

UENUM(BlueprintType)
enum class EABIteractiveObjectTypes : uint8
{
	Food
	UMETA(DisplayName = "Food"),
	Water
	UMETA(DisplayName = "Water"),
	Gate
	UMETA(DisplayName = "Gate"),
};

UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABInteractiveObjectBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
	TEnumAsByte<EABIteractiveObjectTypes> IteractiveObjectTypes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bInteracted;

};