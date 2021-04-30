// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABAnimalCharacter.h"
#include "ABDogCharacter.generated.h"

UENUM(BlueprintType)
enum class InteractState : uint8
{
	Pushing	 = 0 UMETA(DisplayName = "Pushing"), 
	Pulling UMETA(DisplayName = "Pulling"), 
	None UMETA(DisplayName = "None")
};

class AABScentIndicator;

UCLASS()
class AHRIANDBEAR_API AABDogCharacter : public AABAnimalCharacter
{
	GENERATED_BODY()
	
public:

	
	AABDogCharacter();
	virtual void UseAbility() override;
	void CatScentTracker();
	void EnterPushMode();
	void SetInteractState(InteractState i_state);

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AABScentIndicator> scentIndicator;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
		InteractState myInteractState = InteractState::None;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
		bool myIsPulling = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	EABAnimalMovementNoiseVolume GetSprintMovementVolume() const override { return EABAnimalMovementNoiseVolume::Loud; }

	
	bool myIsPushing = false;
};
