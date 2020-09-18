// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Movement
	// Handles input for moving forward and backward.
	UFUNCTION(Category = "Movement")
		void WalkForward(float Value);
	
	// Handles input for moving right and left.
	UFUNCTION(Category = "Movement")
		void WalkRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION(Category = "Movement")
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION(Category = "Movement")
		void StopJump();
#pragma endregion 

#pragma region Component
	////FPS camera.
	//UPROPERTY(VisibleAnywhere, Category = Component)
	//	class UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Component)
		USkeletalMeshComponent* FPSMesh;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Component)
		USpringArmComponent* FPSSpringArm;
#pragma endregion 
};
