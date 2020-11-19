// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimalCharacter.h"
#include "ABPlayerController.h"
#include "Interactives/Interactive.h"
#include "AABSurvivalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Components/SphereComponent.h"
#include "Interactives/ABClimbZone.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/InputComponent.h"
#include "Interactives/CharacterInteractionComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AABAnimalCharacter::AABAnimalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	camera->SetupAttachment(springArm);

	ProjectileStart = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileStart"));
	ProjectileStart->SetupAttachment(RootComponent);

	InteractionComponent = CreateDefaultSubobject<UCharacterInteractionComponent>(TEXT("InteractionComp"));
	InteractionComponent->SetupAttachment(RootComponent);

	SurvivalComponent = CreateDefaultSubobject<UAABSurvivalComponent>(TEXT("Survival Component"));

	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;
	cameraLerpSpeed = 2.0f;

	bWithinRange = false;
	bIsFollowing = false;

	bBlackBoardSet = false;

	bInClimbingZone = false;
	bClimbing = false;

	bAttached = false;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void AABAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetOtherAnimal();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	FPCameraTargetLocation.X = camera->GetRelativeLocation().X;

	OriginalSpringArmLength = springArm->TargetArmLength;
	OriginalCameraPosition = camera->GetRelativeLocation();
}

bool AABAnimalCharacter::CanJumpInternal_Implementation() const
{
	return Super::CanJumpInternal_Implementation() && bCanJump;
}

// Called every frame
void AABAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangeMovementMode();
	ChangeCameraLocation(DeltaTime);
	SprintStaminaUpdate(DeltaTime);
}

void AABAnimalCharacter::Jump()
{
	LaunchCharacter(JumpingVelocity, true, true);
}

void AABAnimalCharacter::UpdateChecking()
{
	if (SurvivalComponent->Stamina.CurrentValue < JumpStamina)
	{
		bCanJump = false;
		return;
	}

	bCanJump = CheckJumping(JumpingVelocity);
}

void AABAnimalCharacter::StartJumping()
{
	bJumping = true;

	FTimerDelegate JumpTimerDelegate = FTimerDelegate::CreateUObject(this, &AABAnimalCharacter::EndJumping);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, JumpTimerDelegate, 0.5f, false);
}

void AABAnimalCharacter::EndJumping()
{
	bJumping = false;
}

void AABAnimalCharacter::StartSprinting()
{
	if (SurvivalComponent->Stamina.CurrentValue <= 0)
	{
		return;
	}

	bSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AABAnimalCharacter::SprintStaminaUpdate(float DeltaTime)
{
	UABSurvivalStatFunctions::AddToCurrentValue(SurvivalComponent->Stamina, -SprintStaminaRateOfChange * DeltaTime);
	if (SurvivalComponent->Stamina.CurrentValue <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("end sprinting"));
		EndSprinting();
	}
}

void AABAnimalCharacter::EndSprinting()
{
	bSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AABAnimalCharacter::StartCrouch()
{
	bCrouching = true;
	GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
	GetCharacterMovement()->bWantsToCrouch = true;
	//GetCharacterMovement()->Crouch();
	//GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AABAnimalCharacter::EndCrouch()
{
	bCrouching = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->bWantsToCrouch = false;
	//GetCharacterMovement()->UnCrouch();
	//GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = false;
}

void AABAnimalCharacter::ChangeOtherFollowingStatus()
{
	if (OtherAnimal)
	{
		if (OtherAnimal->bIsFollowing == false)
		{
			OtherAnimal->bIsFollowing = true;
		}
		else
		{
			OtherAnimal->bIsFollowing = false;
			OtherAnimal->GetMovementComponent()->StopMovementImmediately();
		}
	}
}

void AABAnimalCharacter::SwitchAnimal()
{
	bIsFollowing = false;
	GetMovementComponent()->StopMovementImmediately();

	OtherAnimal->bIsFollowing = false;
	OtherAnimal->GetMovementComponent()->StopMovementImmediately();

	if (OtherAnimal && GetController())
	{
		AController* tempPlayerController = GetController();
		AController* tempAIController = OtherAnimal->GetController();
		if (tempPlayerController && tempAIController)
		{
			tempPlayerController->UnPossess();
			tempAIController->UnPossess();

			tempPlayerController->Possess(OtherAnimal);
			tempAIController->Possess(this);
			
			if (OtherAnimal->InteractionComponent->IsInteracting())
			{
				Cast<AABPlayerController>(tempPlayerController)->UnbindInput();
				OtherAnimal->InteractionComponent->GetInteractingActor()->BindInput(tempPlayerController->InputComponent);
			}
			else
			{
				Cast<AABPlayerController>(tempPlayerController)->BindInput();
			}
		}
	}

	OtherAnimal->bBlackBoardSet = false;
}

void AABAnimalCharacter::ChangeMovementSetting()
{
	GetCharacterMovement()->bOrientRotationToMovement = bOrientRotationToMovementSetting;
}

void AABAnimalCharacter::ChangeMovementMode()
{
	if (bClimbing == false && GetMovementComponent()->IsMovingOnGround() == false)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	}
	else if (bClimbing == false)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else if (bClimbing == true)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
}

void AABAnimalCharacter::LerpCameraToFP(float DeltaTime)
{
	const float dist = FVector::Dist(camera->GetRelativeLocation(), FPCameraTargetLocation) / 100.f;

	if (dist >= 0.01)
	{
		FVector temp = FMath::Lerp(camera->GetRelativeLocation(), FPCameraTargetLocation, cameraLerpSpeed * DeltaTime);
		camera->SetRelativeLocation(temp);

		float length = FMath::Lerp(springArm->TargetArmLength, FPSpringArmTargetLength, cameraLerpSpeed * DeltaTime);
		springArm->TargetArmLength = length;
	}
}

void AABAnimalCharacter::LerpCameraToTP(float DeltaTime)
{
	const float dist = FVector::Dist(camera->GetRelativeLocation(), OriginalCameraPosition) / 100.f;

	if (dist >= 0.01)
	{
		FVector temp = FMath::Lerp(camera->GetRelativeLocation(), OriginalCameraPosition, cameraLerpSpeed * DeltaTime);
		camera->SetRelativeLocation(temp);

		float length = FMath::Lerp(springArm->TargetArmLength, OriginalSpringArmLength, cameraLerpSpeed * DeltaTime);
		springArm->TargetArmLength = length;
	}
}

void AABAnimalCharacter::ChangeCameraLocation(float DeltaTime)
{
	if (bCrouching == true)
	{
		LerpCameraToFP(DeltaTime);
	}
	else
	{
		LerpCameraToTP(DeltaTime);
	}
}

void AABAnimalCharacter::UseAbility()
{

}

void AABAnimalCharacter::SetOtherAnimal()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABAnimalCharacter::StaticClass(), FoundActors);

	for (AActor* animal : FoundActors) {
		if (this != animal) {
			OtherAnimal = Cast<AABAnimalCharacter>(animal);
		}
	}
}

bool AABAnimalCharacter::CheckJumping(FVector& OutVelocity)
{
	FVector launchVel = (GetActorRotation().RotateVector(FVector::UpVector) + GetActorRotation().RotateVector(FVector::ForwardVector)) * 0.707f * JumpingSpeed;
	FPredictProjectilePathParams inParams = FPredictProjectilePathParams(3.0f, ProjectileStart->GetComponentLocation(), launchVel, 2.0f, ECollisionChannel::ECC_Visibility, this);
	if (bDebugJumping)
	{
		inParams.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	}
	FPredictProjectilePathResult outParams;
	bool hasHole = false;
	if (!UGameplayStatics::PredictProjectilePath(GetWorld(), inParams, outParams))
	{
		return false;
	}
	TArray<AActor*> actorsToIgnore;
	FHitResult groundHit;
	float holeDiff = 0.f;
	for (auto& p : outParams.PathData)
	{
		float heightDiff;
		FCollisionQueryParams param1 = FCollisionQueryParams(FName(), false, this);
		param1.bDebugQuery = true;
		FCollisionResponseParams param2 = FCollisionResponseParams();
		if (!GetWorld()->LineTraceSingleByChannel(
			groundHit,
			p.Location,
			p.Location + FVector::DownVector * 500.f,
			ECollisionChannel::ECC_Visibility,
			param1,
			param2))
		{
			hasHole = true;
			continue;
		}
		else
		{
			if (bDebugJumping)
				DrawDebugLine(GetWorld(), p.Location, groundHit.Location, FColor::Red);
			heightDiff = groundHit.Location.Z - ProjectileStart->GetComponentLocation().Z;
			bool canJump = false;
			canJump |= (hasHole && heightDiff < MinJumpDepth&& heightDiff > MaxJumpDepth && heightDiff - holeDiff > MinJumpHeight);
			canJump |= (heightDiff - holeDiff > MinJumpHeight && heightDiff < MaxJumpHeight && (heightDiff > MinJumpHeight || hasHole));
			if (canJump)
			{
				FVector tossVel;
				FVector endLoc = groundHit.Location + GetActorRotation().RotateVector(FVector::ForwardVector * EdgeForwardOffset);
				if (!UGameplayStatics::SuggestProjectileVelocity(GetWorld(), tossVel, ProjectileStart->GetComponentLocation(), endLoc, JumpingSpeed, true, 10.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
				{
					return false;
				}
				if (bDebugJumping)
					UKismetSystemLibrary::DrawDebugSphere(GetWorld(), endLoc, 10.f, 12, FLinearColor::Yellow);
				OutVelocity = tossVel;
				return true;
			}
		}
		hasHole = heightDiff < MinJumpDepth;
		holeDiff = heightDiff;
	}
	return false;
}
