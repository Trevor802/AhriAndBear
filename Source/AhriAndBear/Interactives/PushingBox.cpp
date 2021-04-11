// Fill out your copyright notice in the Description page of Project Settings.


#include "PushingBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
//#include "Interactives/CharacterInteractionComponent.h"
#include "ABAnimalCharacter.h"
#include "ABPlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Characters/ABDogCharacter.h"
#include "Math/TransformNonVectorized.h"

// My testing showed that this works as expected.
constexpr float INTERACTABLE_ANGLE_THRESHOLD_RADIANS = 2;

APushingBox::APushingBox()
{
	PrimaryActorTick.bCanEverTick = true;

	//sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	//SetRootComponent(sceneRoot);

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(collider);
	// collider->SetupAttachment(RootComponent);
	// collider->SetupAttachment(RootComponent);
	// RootComponent = collider;

	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	boxMesh->SetupAttachment(RootComponent);

	BoxJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("BoxJoint"));
	BoxJoint->SetupAttachment(RootComponent);
	BoxJoint->SetDisableCollision(true);

	trigger_left = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Trigger"));
	trigger_left->SetupAttachment(RootComponent);
	//trigger_left->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Left);

	trigger_right = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Trigger"));
	trigger_right->SetupAttachment(RootComponent);
	//trigger_right->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Right);

	trigger_front = CreateDefaultSubobject<UBoxComponent>(TEXT("Forward Trigger"));
	trigger_front->SetupAttachment(RootComponent);
	//trigger_front->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Front);

	trigger_back = CreateDefaultSubobject<UBoxComponent>(TEXT("Back Trigger"));
	trigger_back->SetupAttachment(RootComponent);
	//trigger_back->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Back);

	//trigger_left->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	//trigger_right->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	//trigger_front->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	//trigger_back->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);

	bHeld = false;
}

APushingBox::APushingBox(const FObjectInitializer& OI)
{
	PrimaryActorTick.bCanEverTick = true;

	//sceneRoot = OI.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene Root"));
	//SetRootComponent(sceneRoot);

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(collider);
	//collider->SetupAttachment(RootComponent);
	// collider->SetupAttachment(RootComponent);
	// RootComponent = collider;

	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	boxMesh->SetupAttachment(RootComponent);

	BoxJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("BoxJoint"));
	BoxJoint->SetupAttachment(RootComponent);
	BoxJoint->SetDisableCollision(true);

	trigger_left = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Trigger"));
	trigger_left->SetupAttachment(RootComponent);

	trigger_right = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Trigger"));
	trigger_right->SetupAttachment(RootComponent);

	trigger_front = CreateDefaultSubobject<UBoxComponent>(TEXT("Forward Trigger"));
	trigger_front->SetupAttachment(RootComponent);

	trigger_back = CreateDefaultSubobject<UBoxComponent>(TEXT("Back Trigger"));
	trigger_back->SetupAttachment(RootComponent);

	bHeld = false;
}

void APushingBox::BeginPlay()
{
	Super::BeginPlay();

	horizontal = false;
	verticle = false;
	myInteractPosition = InteractPosition::None;

	trigger_left->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Left);
	trigger_right->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Right);
	trigger_front->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Front);
	trigger_back->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Back);

	trigger_left->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	trigger_right->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	trigger_front->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	trigger_back->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);

	myCollisionParams.AddIgnoredActor(this);
	//collider->SetSimulatePhysics(true);
	//collider->GetBodyInstance()->bLockXRotation = true;
	//collider->GetBodyInstance()->bLockYRotation = true;
	//collider->GetBodyInstance()->bLockZRotation = true;

	//collider->GetBodyInstance()->bLockZTranslation = true;
	//LockMeshLocation();
}

bool APushingBox::CanInteract(UCharacterInteractionComponent* interactingComponent) const {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Can we interact?"));
	if (!Super::CanInteract(interactingComponent)) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't"));
		return false;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Reeee"));
	auto actor = GET_CHARACTER(interactingComponent);
	if (!actor) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Nani the heck?"));
		return false;
	}
	auto vec2Box = (GetActorLocation() - actor->GetActorLocation()).GetSafeNormal();
	auto dot = FVector::DotProduct(vec2Box, FVector::UpVector);
	auto angle = acos(dot);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Dot: %f | Angle: %f"), dot, angle));
	return angle < INTERACTABLE_ANGLE_THRESHOLD_RADIANS;
}

void APushingBox::BeginInteraction()
{
	auto character = GET_CHARACTER(InteractingComponent);
	AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
	if (dogCharacter && myInteractPosition != InteractPosition::None)
	{
		dogCharacter->bOrientRotationToMovementSetting = false;
		dogCharacter->ChangeMovementSetting();

		//BoxJoint->SetConstrainedComponents(boxMesh, "", dogCharacter->GetMesh(), "");
		bHeld = true;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("attach box"));
		//collider->SetSimulatePhysics(false);
		//collider->SetEnableGravity(false);
		dogCharacter->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		//AttachToComponent(character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		characterRotater = dogCharacter->GetActorRotation();
		characterTransform = dogCharacter->GetActorTransform();
		myCollisionParams.AddIgnoredActor(dogCharacter);
		// Setup direction 
		switch (myInteractPosition)
		{
		case InteractPosition::Front:
			myPushDirection = GetActorForwardVector();
			currentTrigger = trigger_front;
			interactTransform = trigger_front->GetComponentTransform();
			break;
		case InteractPosition::Back:
			myPushDirection = -GetActorForwardVector();
			currentTrigger = trigger_back;
			interactTransform = trigger_back->GetComponentTransform();
			break;
		case InteractPosition::Left:
			myPushDirection = -GetActorRightVector();
			currentTrigger = trigger_left;
			interactTransform = trigger_left->GetComponentTransform();
			break;
		case InteractPosition::Right:
			myPushDirection = GetActorRightVector();
			currentTrigger = trigger_right;
			interactTransform = trigger_right->GetComponentTransform();
			break;
		default:
			myPushDirection = GetActorForwardVector();
			break;
		}
	}

}

void APushingBox::EndInteraction(bool)
{
	//DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Detach box"));
	bHeld = false;
	//BoxJoint->SetConstrainedComponents(nullptr, NAME_None, nullptr, NAME_None);
	//BoxJoint->BreakConstraint();

	auto character = GET_CHARACTER(InteractingComponent);
	AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
	if (dogCharacter)
	{
		dogCharacter->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		dogCharacter->bOrientRotationToMovementSetting = true;
		dogCharacter->ChangeMovementSetting();
	}

	myCollisionParams.ClearIgnoredActors();
	myCollisionParams.AddIgnoredActor(this);

	moveValue = 0.f;
	currentTrigger = nullptr;
	isInPosition = false;
	//collider->SetSimulatePhysics(true);
	//collider->SetEnableGravity(true);
}

void APushingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateBox();
	if (bHeld && !isInPosition)
	{
		auto character = GET_CHARACTER(InteractingComponent);
		AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
		if (dogCharacter)
		{
			// Lerp into push position
			float lerpProgress = FMath::Clamp(enterPositionTimer / enterPositionDuration, 0.f, 1.f);
			FVector lerpPos = FMath::Lerp(characterTransform.GetLocation(), currentTrigger->GetComponentLocation(), lerpProgress);
			FRotator lerpRot = FMath::Lerp(characterTransform.GetRotation().Rotator(), currentTrigger->GetComponentRotation(), lerpProgress);
			//dogCharacter->SetActorLocation(lerpPos);
			dogCharacter->SetActorLocationAndRotation(lerpPos, lerpRot.Quaternion());
			enterPositionTimer += DeltaTime;

			if (lerpProgress >= 1.f)
			{
				enterPositionTimer = 0.f;
				isInPosition = true;
			}
		}
		
	}

	if (myInteractPosition != InteractPosition::None && moveValue != 0.f && isInPosition)
	{
		if (CheckBoxMoveable())
		{
			FVector movePosition = GetActorLocation() + myPushDirection * moveValue * pushingSpeed * DeltaTime;
			SetActorLocation(movePosition);
		}
		
	}
}

void APushingBox::UpdateBox()
{
	//if (BoxJoint->ConstraintInstance.IsBroken() && bHeld)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Broke"));
	//	EndInteraction(true);
	//	AfterInteraction(true);
	//}
}

bool APushingBox::CheckBoxMoveable()
{
	FCollisionShape shape = FCollisionShape::MakeBox(collider->GetScaledBoxExtent() * 0.9f);
	FHitResult sweepResult;
	auto character = GET_CHARACTER(InteractingComponent);
	AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
	
	FVector sweepStartPosition = moveValue < 0.f ? GetActorLocation() : dogCharacter->GetActorLocation();
	FVector sweepEndPosition = moveValue < 0.f ?
		GetActorLocation() + (myPushDirection * collider->GetScaledBoxExtent() / 2 + myPushDirection * 20.f)
		: (dogCharacter->GetActorLocation() - currentTrigger->GetForwardVector() * 50.f);
	
	if (GetWorld()->SweepSingleByChannel(
		sweepResult,
		sweepStartPosition,
		sweepEndPosition,
		collider->GetComponentRotation().Quaternion(),
		ECC_Visibility,
		shape,
		myCollisionParams))
		return false;
	else
		return true;
}

void APushingBox::OnOverlapBegin_Left(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (Cast<AABDogCharacter>(OtherActor))
		myInteractPosition = InteractPosition::Left;
}

void APushingBox::OnOverlapBegin_Right(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (Cast<AABDogCharacter>(OtherActor))
		myInteractPosition = InteractPosition::Right;
}

void APushingBox::OnOverlapBegin_Front(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (Cast<AABDogCharacter>(OtherActor))
		myInteractPosition = InteractPosition::Front;
}

void APushingBox::OnOverlapBegin_Back(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (Cast<AABDogCharacter>(OtherActor))
		myInteractPosition = InteractPosition::Back;
}

void APushingBox::CallMoveForward(float value)
{
	if (InteractingComponent)
	{
		moveValue = -value;
		//Super::CallMoveForward(value);
	}
}

void APushingBox::CallMoveRight(float value)
{
	if(InteractingComponent)
	{
		auto character = GET_CHARACTER(InteractingComponent);
		AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
		if (dogCharacter)
			return;
		else
			Super::CallMoveRight(value);
	}
}

void APushingBox::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (Cast<AABDogCharacter>(OtherActor))
		myInteractPosition = InteractPosition::None;
}

void APushingBox::LockMeshLocation()
{

	boxMesh->GetBodyInstance()->bLockZTranslation = true;
	boxMesh->GetBodyInstance()->bLockYTranslation = true;
	boxMesh->GetBodyInstance()->bLockXTranslation = true;
	boxMesh->SetSimulatePhysics(false);
}

void APushingBox::EnterInteractPosition()
{
	
}