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

protected:
	virtual void BeginPlay() override;

public:
#pragma region Properties

	UPROPERTY(Category = "Enemy|AI", EditAnywhere)
		float SearchLookAngle;

	UPROPERTY(Category = "Enemy|AI", EditAnywhere)
		float DefaultLookAngle;

	UPROPERTY(Category = "Enemy|AI", EditAnywhere)
		float AttackLookAngle;

#pragma endregion

	ABobbyEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AttackPlayer(AActor* playerActor) override;
	void AlertEnemy(AActor* playerActor) override;

	UFUNCTION(Category = "Sense", BlueprintCallable)
		void SetAttackLookAngle();

	UFUNCTION(Category = "Sense", BlueprintCallable)
		void SetSearchLookAngle();

	UFUNCTION(Category = "Sense", BlueprintCallable)
		void SetDefaultLookAngle();
};
