// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimalCharacter.h"
#include "Interactives/ABInteractiveObjectBase.h"
#include "AABSurvivalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Components/SphereComponent.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"
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

	ProjectileStart = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileStart"));
	ProjectileStart->SetupAttachment(RootComponent);

	SurvivalComponent = CreateDefaultSubobject<UAABSurvivalComponent>(TEXT("Survival Component"));

	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;

	bWithinRange = false;
	bIsFollowing = false;

	bBlackBoardSet = false;
}

// Called when the game starts or when spawned
void AABAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetOtherAnimal();

	InterationTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABAnimalCharacter::OnInteractionOverlapBegin);
	InterationTrigger->OnComponentEndOverlap.AddDynamic(this, &AABAnimalCharacter::OnInteractionOverlapEnd);

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

bool AABAnimalCharacter::CanJumpInternal_Implementation() const
{
	return Super::CanJumpInternal_Implementation() && bCanJump;
}

// Called every frame
void AABAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AABAnimalCharacter::Jump()
{
	LaunchCharacter(JumpingVelocity, true, true);
}

void AABAnimalCharacter::UpdateChecking()
{
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

void AABAnimalCharacter::OnInteractionOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<AABInteractiveObjectBase>(OtherActor))
	{
		InteractiveObjectRef = Cast<AABInteractiveObjectBase>(OtherActor);
		bWithinRange = true;
	}
}

void AABAnimalCharacter::OnInteractionOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && Cast<AABInteractiveObjectBase>(OtherActor))
	{
		InteractiveObjectRef = nullptr;
		bWithinRange = false;
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

bool AABAnimalCharacter::CheckJumping(FVector& OutVelocity)
{
	FVector launchVel = (GetActorRotation().RotateVector(FVector::UpVector) + GetActorRotation().RotateVector(FVector::ForwardVector)) * 0.707f * JumpingSpeed;
	FPredictProjectilePathParams inParams = FPredictProjectilePathParams(3.0f, ProjectileStart->GetComponentLocation(), launchVel, 2.0f, ECollisionChannel::ECC_WorldStatic, this);
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
			canJump |= (hasHole && heightDiff < MinDepth&& heightDiff > MaxDepth && heightDiff - holeDiff > MinHeight);
			canJump |= (heightDiff - holeDiff > MinHeight && heightDiff < MaxHeight && (heightDiff > MinHeight || hasHole));
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
		hasHole = heightDiff < MinDepth;
		holeDiff = heightDiff;
	}
	return false;
}
