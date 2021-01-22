// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../EnemyBase.h"

#include "BobbyEnemy.generated.h"

UCLASS()
class AHRIANDBEAR_API ABobbyEnemy : public AEnemyBase
{
	GENERATED_BODY()

private:
	UFUNCTION()
		void HandlePerceptionUpdated(const TArray<AActor*>& Actors);

protected:
	virtual void BeginPlay() override;

public:
	ABobbyEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AttackPlayer(AActor* playerActor) override;
	void AlertEnemy(AActor* playerActor) override;
};
