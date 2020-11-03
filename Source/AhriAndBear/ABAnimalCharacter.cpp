// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimalCharacter.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "AABSurvivalComponent.h"
#include "Interactives/ABClimbZone.h"
#include "Engine.h"
#include "Components/InputComponent.h"
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

	InterationTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InterationTrigger"));
	InterationTrigger->SetupAttachment(RootComponent);

	SurvivalComponent = CreateDefaultSubobject<UAABSurvivalComponent>(TEXT("Survival Component"));

	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;
	cameraLerpSpeed = 2.0f;

	bWithinRange = false;
	bIsFollowing = false;

	bBlackBoardSet = false;

	bInClimbingZone = false;
	bClimbing = false;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void AABAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetOtherAnimal();

	InterationTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABAnimalCharacter::OnInteractionOverlapBegin);
	InterationTrigger->OnComponentEndOverlap.AddDynamic(this, &AABAnimalCharacter::OnInteractionOverlapEnd);

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	OriginalCameraPosition = camera->GetRelativeLocation();
}

// Called every frame
void AABAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangeMovementMode();
	ChangeCameraLocation(DeltaTime);
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
	bSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AABAnimalCharacter::EndSprinting()
{
	bSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AABAnimalCharacter::StartInteracting()
{
	if (InteractiveObjectRef && InteractiveObjectRef->CanInteract() == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("interaction succeed"));
		bInteracting = true;

		float InteractingCooldown = 0.0f;

		InteractingCooldown = InteractiveObjectRef->InteractionDelay;

		FTimerDelegate InteractionTimerDelegate = FTimerDelegate::CreateUObject(this, &AABAnimalCharacter::EndInteracting);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, InteractionTimerDelegate, InteractingCooldown, false);
	}
}

void AABAnimalCharacter::EndInteracting()
{
	bInteracting = false;
	InteractiveObjectRef->AfterInteraction();
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
	}
}

void AABAnimalCharacter::LerpCameraToTP(float DeltaTime)
{
	const float dist = FVector::Dist(camera->GetRelativeLocation(), OriginalCameraPosition) / 100.f;

	if (dist >= 0.01)
	{
		FVector temp = FMath::Lerp(camera->GetRelativeLocation(), OriginalCameraPosition, cameraLerpSpeed * DeltaTime);

		camera->SetRelativeLocation(temp);
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

bool AABAnimalCharacter::CanMove()
{
	if (bInteracting == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AABAnimalCharacter::CanSprint()
{
	if (CanMove() && bJumping == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool AABAnimalCharacter::CanInteract()
{
	if (bInteracting == true || bWithinRange == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AABAnimalCharacter::CanUseAbility()
{
	if (bInteracting == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AABAnimalCharacter::CanClimb()
{
	if (bInClimbingZone == true && bSprinting == true && AnimalType == EAnimalType::Cat)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AABAnimalCharacter::CanCrouch()
{
	if (CanMove() == true && bSprinting == false && GetMovementComponent()->IsMovingOnGround() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AABAnimalCharacter::OnInteractionOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<AABInteractiveObjectBase>(OtherActor))
	{
		InteractiveObjectRef = Cast<AABInteractiveObjectBase>(OtherActor);
		bWithinRange = true;
	}

	if (OtherActor && OtherActor != this && Cast<AABClimbZone>(OtherActor))
	{
		bInClimbingZone = true;
	}
}

void AABAnimalCharacter::OnInteractionOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && Cast<AABInteractiveObjectBase>(OtherActor))
	{
		InteractiveObjectRef = nullptr;
		bWithinRange = false;
	}

	if (OtherActor && OtherActor != this && Cast<AABClimbZone>(OtherActor))
	{
		bInClimbingZone = false;
	}
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
