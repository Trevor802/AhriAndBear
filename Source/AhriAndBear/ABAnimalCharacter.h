// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "Components/BoxComponent.h"
#include "GameBase/Define.h"
#include "ABAnimalCharacter.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartJumping();
	void EndJumping();

	void StartSprinting();
	void EndSprinting();

	void StartInteracting();
	void EndInteracting();

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

public:
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float baseTurnRate;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float baseLookUpRate;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		float WalkSpeed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		float SprintSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool bJumping;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool bSprinting;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		bool bInteracting;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EAnimalType AnimalType;

private:
	bool bWithinRange;
	AABInteractiveObjectBase* InteractiveObjectRef;
};
