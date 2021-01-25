// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../EnemyBase.h"

#include "CrierEnemy.generated.h"

UCLASS()
class AHRIANDBEAR_API ACrierEnemy : public AEnemyBase
{
	GENERATED_BODY()

private:
	UFUNCTION()
		void HandlePerceptionUpdated(const TArray<AActor*>& Actors);
	void UpdateAlertCounter(float deltaTime);

	int _currentAlertCount;
	float _alertDelayTimer;

protected:
	virtual void BeginPlay() override;

public:
#pragma region Properties

	UPROPERTY(Category = "Enemy|Data", EditAnywhere)
		USoundBase* EnemySound;

	UPROPERTY(Category = "Enemy|Data", EditAnywhere)
		int AlertTimesCount;

	UPROPERTY(Category = "Enemy|Data", EditAnywhere)
		float AlertDelayTime;

#pragma endregion

	ACrierEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AttackPlayer(AActor* playerActor) override;
	void AlertEnemy(AActor* playerActor) override;
};
