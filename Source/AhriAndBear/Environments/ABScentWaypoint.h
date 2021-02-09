// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABScentWaypoint.generated.h"

class USphereComponent;
class AABScentSource;
class AABScentIndicator;

UCLASS()
class AHRIANDBEAR_API AABScentWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AABScentWaypoint();
	AABScentWaypoint* GetReachableWaypoint(AABScentSource* targetSource);
	bool IsSourceReachable(AABScentSource* targetSource);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		USphereComponent* waypointCollider;

	bool isQueried = false;
};
