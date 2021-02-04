// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../EnemyBase.h"

#include "CrierEnemy.generated.h"

class UAIPerceptionComponent;

UCLASS()
class AHRIANDBEAR_API ACrierEnemy : public AEnemyBase
{
	GENERATED_BODY()

private:
	UAIPerceptionComponent* _perceptionComponent;

protected:
	virtual void BeginPlay() override;

public:
#pragma region Properties

	UPROPERTY(Category = "Enemy|Data", EditAnywhere)
		USoundBase* EnemySound;

#pragma endregion

	ACrierEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
