// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameBase/AccessibilitySettings.h"
#include "AABSurvivalComponent.h"
#include "AhriAndBearGameModeBase.generated.h"

class AABCatCharacter;
class AABDogCharacter;
class UUserSettings;

/**
* Provides the reason why a game 
*/
UENUM(BlueprintType)
enum class EGameOverReason : uint8 {
	GO_AnimalCaught UMETA(DisplayName="Animal Was Caught"),
	GO_AnimalsDead UMETA(DisplayName="Animals Died"),
	GO_Victory UMETA(DisplayName="Victory"),
};

USTRUCT(Blueprintable, Category = "Game Mode | Events")
struct FGameOverInfo {
	GENERATED_BODY()
public:
	FGameOverInfo() {}

	FGameOverInfo(EGameOverReason reason) :
		Reason(reason)
	{}

	UPROPERTY(BlueprintReadonly, Category = "Game Mode | Events")
		EGameOverReason Reason;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameOver, const FGameOverInfo&, context);

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AAhriAndBearGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tasks")
		TArray<FString> LevelTasks;
	UPROPERTY(BlueprintReadOnly, Category = "Tasks")
		FString CurTaskText;

	int CurTaskIndex;

	UPROPERTY(BlueprintAssignable, Category = "Game Mode | Events")
		FGameOver OnGameOver;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Mode | Settings | Accessibility")
		FAccessibilitySettings AccessibilitySettings;

public:
	AAhriAndBearGameModeBase();
	virtual void BeginPlay() override;
	void ToNextTask();

	UFUNCTION()
	void OnAnimalCriticalConditionChanged(UAABSurvivalComponent* sender, const FAnimalCriticalConditionChangedInfo& info);

	UFUNCTION()
	void OnAnimalCaught(AActor* captor);

	UFUNCTION(BlueprintCallable, Category = "Game Mode")
		void EndGame(EGameOverReason reason);

private:
	AABCatCharacter* cat;
	AABDogCharacter* dog;
};
