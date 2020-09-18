// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "ABAnimalCharacter.h"

// Sets default values
AABAnimalCharacter::AABAnimalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;
	
	FPSSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FPSSpringArm"));
	FPSSpringArm->SetupAttachment(GetCapsuleComponent());


}

// Called when the game starts or when spawned
void AABAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AABAnimalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" binding
	PlayerInputComponent->BindAxis("WalkForward", this, &AABAnimalCharacter::WalkForward);
	PlayerInputComponent->BindAxis("WalkRight", this, &AABAnimalCharacter::WalkRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AABAnimalCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AABAnimalCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AABAnimalCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AABAnimalCharacter::StopJump);
}

void AABAnimalCharacter::WalkForward(float Value)
{
	if(Value)
	{
		// Find out which way is "forward" and record that the player wants to move that way.
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("X: %f"), Direction.X));
	}
}

void AABAnimalCharacter::WalkRight(float Value)
{
	if(Value)
	{
		// Find out which way is "forward" and record that the player wants to move that way.
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("X: %f"), Direction.X));
	}
}

void AABAnimalCharacter::StartJump()
{
	bPressedJump = true;
}

void AABAnimalCharacter::StopJump()
{
	bPressedJump = false;
}