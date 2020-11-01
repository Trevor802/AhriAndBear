// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameBase/Define.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ABAnimalCharacter.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class AABInteractiveObjectBase;
class UAABSurvivalComponent;
class UPawnSensingComponent;
class UPawnNoiseEmitterComponent;
class UAudioComponent;

UCLASS()
class AHRIANDBEAR_API AABAnimalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABAnimalCharacter();

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite)
		class USpringArmComponent* springArm;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite)
		class UCameraComponent* camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* InterationTrigger;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class USphereComponent* ProjectileStart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival")
		UAABSurvivalComponent* SurvivalComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float JumpingSpeed = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float MinDepth = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float MaxDepth = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float MinHeight = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float MaxHeight = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float EdgeForwardOffset = 500.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool CanJumpInternal_Implementation() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;
	void StartJumping();
	void EndJumping();

	void StartSprinting();
	void EndSprinting();

	void StartInteracting();
	void EndInteracting();

	void ChangeOtherFollowingStatus();

	void SwitchAnimal();

	void ChangeMovementSetting();

	virtual void UseAbility();
	bool CanMove();
	bool CanSprint();
	bool CanInteract();
	bool CanUseAbility();

	UFUNCTION()
	void OnInteractionOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractionOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	FTimerHandle TimerHandle;
	void SetOtherAnimal();

public:
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float baseTurnRate;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float baseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SprintSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool bJumping;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool bSprinting;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool bInteracting;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EAnimalType AnimalType;

	UPROPERTY(BlueprintReadWrite)
		bool bIsFollowing;

	AABAnimalCharacter* OtherAnimal;
	bool bBlackBoardSet;
	bool bOrientRotationToMovementSetting;

private:
	bool bWithinRange;
	AABInteractiveObjectBase* InteractiveObjectRef;
	bool CheckJumping(FVector&);
	bool bCanJump;
	FVector JumpingVelocity;
};
