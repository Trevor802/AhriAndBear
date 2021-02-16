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
		float JumpStamina = 25;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay|Jumping")
		float EdgeForwardOffset = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
		bool bDebugJumping = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay|Sprint")
		float SprintStaminaRateOfChange = 1;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
		FBark OnAnimalBark;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool CanJumpInternal_Implementation() const override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;
	void UpdateChecking();
	void StartJumping();
	void EndJumping();

	void StartSprinting();
	void EndSprinting();
	void SprintStaminaUpdate(float DeltaTime);

	void StartCrouch();
	void EndCrouch();

	void StartReading();
	void EndReading();

	void ChangeOtherFollowingStatus();

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EAnimalType AnimalType;

	bool bAttached;

	UPROPERTY(BlueprintReadWrite)
		bool bIsFollowing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		class USoundBase* BarkingSound;

	AABAnimalCharacter* OtherAnimal;
	bool bBlackBoardSet;
	bool bOrientRotationToMovementSetting;

	bool bInClimbingZone;
	bool bClimbing;

	bool bReading;

	void GetCaught(AActor* byWhom);

private:
	bool bWithinRange;
	AABInteractiveObjectBase* InteractiveObjectRef;
	bool CheckJumping(FVector&);
	bool bCanJump;
	FVector JumpingVelocity;

	FVector OriginalCameraPosition;
	float OriginalSpringArmLength;
	void HideScentFromCat();
};
