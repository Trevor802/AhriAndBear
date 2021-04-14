// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameBase/Define.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "ABAnimalCharacter.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class AABInteractiveObjectBase;
class UAABSurvivalComponent;
class UABPlayerUIComponent;
class UPawnSensingComponent;
class UPawnNoiseEmitterComponent;
class UAudioComponent;

#define GET_MAIN_CHARACTER Cast<AABAnimalCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBark, FVector, Position);

/**
* Delegate for when an animal begins sprinting.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimalBeganSprinting);

/**
* Delegate for when an animal stops sprinting.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimalStoppedSprinting);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnimalCaught, AActor*, captor);

UENUM(BlueprintType)
enum class EABAnimalMovementNoiseVolume : uint8 {
	Silent UMETA(DisplayName = "No Movement Noise"),
	Quiet UMETA(DisplayName = "Quiet Movement Noise"),
	Normal UMETA(DisplayName = "Normal Movement Noise"),
	Loud UMETA(DisplayName = "Loud Movement Noise"),
};


UCLASS()
class AHRIANDBEAR_API AABAnimalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABAnimalCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay|Interaction")
		class UCharacterInteractionComponent* InteractionComponent;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite)
		class USpringArmComponent* springArm;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite)
		class UCameraComponent* camera;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		class USphereComponent* ProjectileStart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival")
		UAABSurvivalComponent* SurvivalComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		UABPlayerUIComponent* UIComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		UBehaviorTree* BehaviorTree;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
		class UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay|Jumping")
		float JumpingSpeed = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay|Jumping")
		float MinJumpDepth = -100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay|Jumping")
		float MaxJumpDepth = -500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay|Jumping")
		float MinJumpHeight = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay|Jumping")
		float MaxJumpHeight = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay|Jumping")
		float EdgeForwardOffset = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
		bool bDebugJumping = false;

	UPROPERTY(Category = "Gameplay|Combination", BlueprintReadWrite)
		bool AnimalsCombined;

	UPROPERTY(Category = "Gameplay|Combination", BlueprintReadWrite)
		bool AnimalOnTop;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
		FBark OnAnimalBark;

	UPROPERTY(BlueprintAssignable, Category = "Character|Events")
		FAnimalCaught OnAnimalCaught;

	UPROPERTY(BlueprintAssignable, Category = "Character|Events")
		FAnimalBeganSprinting OnSprintStart;

	UPROPERTY(BlueprintAssignable, Category = "Character|Events")
		FAnimalStoppedSprinting OnSprintEnd;

	UFUNCTION(BlueprintPure, Category = "Character | Survival")
		bool IsInCriticalCondition() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool CanJumpInternal_Implementation() const override;
	virtual EABAnimalMovementNoiseVolume GetSprintMovementVolume() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;
	void UpdateChecking();
	void StartJumping();
	void EndJumping();

	void StartSprinting();
	void EndSprinting();
	void UpdateSprinting(float DeltaTime);

	void StartCrouch();
	void EndCrouch();

	void StartReading();
	void EndReading();

	void ChangeOtherFollowingStatus();

	UFUNCTION(BlueprintCallable)
		void SwitchAnimal();
	void Bark();
	void ChangeMovementSetting();
	void ChangeMovementMode();

	void LerpCameraToFP(float DeltaTime);
	void LerpCameraToTP(float DeltaTime);
	void ChangeCameraLocation(float DeltaTime);

	virtual void UseAbility();

protected:
	FTimerHandle TimerHandle;
	void SetOtherAnimal();

public:
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float baseTurnRate;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float baseLookUpRate;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float cameraLerpSpeed;
	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FVector FPCameraTargetLocation;
	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float FPSpringArmTargetLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrouchSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool bCrouching;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool bJumping;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bSprinting;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bInteracting;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bClimbing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EAnimalType AnimalType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsHidden;

	bool bAttached;

	UPROPERTY(BlueprintReadWrite)
		bool bIsFollowing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundBase* BarkingSound;

	UFUNCTION(Category = "Event", BlueprintImplementableEvent)
		void BeforeCharacterSwitch();

	UPROPERTY(Category = "Animal", BlueprintReadOnly)
		AABAnimalCharacter* OtherAnimal;
	bool bBlackBoardSet;
	bool bOrientRotationToMovementSetting;

	bool bInClimbingZone;
	float TargetClimbingRotation;
	float ClimbingRotationRate;

	UFUNCTION(Category = "Gameplay|Sprint", BlueprintImplementableEvent)
		void SprintUpdate();
	bool bReading;

	UFUNCTION(BlueprintCallable, Category = "Character")
		void GetCaught(AActor* byWhom);

	UFUNCTION(BlueprintPure, Category = "Character")
		virtual EABAnimalMovementNoiseVolume GetCurrentMovementVolume() const;

	bool bShowHint;
	FString HintString;

private:
	bool bWithinRange;
	AABInteractiveObjectBase* InteractiveObjectRef;
	bool CheckJumping(FVector&);
	bool bCanJump;
	FVector JumpingVelocity;

	FVector OriginalCameraPosition;
	float OriginalSpringArmLength;
	void HideScentFromCat();

	void CheckClimbingRotation();
};