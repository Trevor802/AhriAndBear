// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

UCLASS()
class AHRIANDBEAR_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = "AI", BlueprintReadOnly, VisibleDefaultsOnly)
		class UAIPerceptionComponent* PerceptionComponent;

	UAISenseConfig_Sight* SightConfig;
	UAISenseConfig_Hearing* HearingConfig;

	virtual void BeginPlay() override;

public:
	AEnemyBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AttackPlayer(AActor* playerActor);
	virtual void AlertEnemy(AActor* playerActor);
};
