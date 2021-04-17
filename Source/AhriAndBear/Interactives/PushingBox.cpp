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
#include "DrawDebugHelpers.h"

// My testing showed that this works as expected.
constexpr float INTERACTABLE_ANGLE_THRESHOLD_RADIANS = 2;

//APushingBox::APushingBox()
//{
//	PrimaryActorTick.bCanEverTick = true;
//
//	//sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
//	//SetRootComponent(sceneRoot);
//
//	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
//	SetRootComponent(collider);
//	// collider->SetupAttachment(RootComponent);
//	// collider->SetupAttachment(RootComponent);
//	// RootComponent = collider;
//
//	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
//	boxMesh->SetupAttachment(RootComponent);
//
//	BoxJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("BoxJoint"));
//	BoxJoint->SetupAttachment(RootComponent);
//	BoxJoint->SetDisableCollision(true);
//
//	trigger_left = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Trigger"));
//	trigger_left->SetupAttachment(RootComponent);
//	//trigger_left->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Left);
//
//	trigger_right = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Trigger"));
//	trigger_right->SetupAttachment(RootComponent);
//	//trigger_right->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Right);
//
//	trigger_front = CreateDefaultSubobject<UBoxComponent>(TEXT("Forward Trigger"));
//	trigger_front->SetupAttachment(RootComponent);
//	//trigger_front->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Front);
//
//	trigger_back = CreateDefaultSubobject<UBoxComponent>(TEXT("Back Trigger"));
//	trigger_back->SetupAttachment(RootComponent);
//	//trigger_back->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Back);
//
//	//trigger_left->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
//	//trigger_right->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
//	//trigger_front->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
//	//trigger_back->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
//
//	bHeld = false;
//}

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

	//trigger_left->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Left);
	//trigger_right->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Right);
	//trigger_front->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Front);
	//trigger_back->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::OnOverlapBegin_Back);

	//trigger_left->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	//trigger_right->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	//trigger_front->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);
	//trigger_back->OnComponentEndOverlap.AddDynamic(this, &APushingBox::OnOverlapEnd);

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
	if (myInteractPosition != InteractPosition::None)
		return false;
	if (NotInteractable)
		return false;
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
	if (dogCharacter)
	{
		dogCharacter->bOrientRotationToMovementSetting = false;
		dogCharacter->ChangeMovementSetting();
		dogCharacter->SetInteractState(InteractState::Pulling);

		//BoxJoint->SetConstrainedComponents(boxMesh, "", dogCharacter->GetMesh(), "");
		bHeld = true;
		CheckInteractDirection();

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("attach box"));
		//collider->SetSimulatePhysics(false);
		//collider->SetEnableGravity(false);
		dogCharacter->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		//AttachToComponent(character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		characterRotater = dogCharacter->GetActorRotation();
		characterTransform = dogCharacter->GetActorTransform();
		myCollisionParams.AddIgnoredActor(dogCharacter);
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
		dogCharacter->SetInteractState(InteractState::None);
		dogCharacter->myIsPulling = false;
	}

	myCollisionParams.ClearIgnoredActors();
	myCollisionParams.AddIgnoredActor(this);

	moveValue = 0.f;
	currentTrigger = nullptr;
	isInPosition = false;
	myInteractPosition = InteractPosition::None;

	//collider->SetSimulatePhysics(true);
	//collider->SetEnableGravity(true);
}

bool APushingBox::IsSameDirection(InteractPosition i_position)
{
	auto character = GET_CHARACTER(InteractingComponent);
	AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
	if (!dogCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("PushingBox.cpp : character not found."));
		return false;
	}
	FVector boxToDog = dogCharacter->GetActorLocation() - GetActorLocation();
	bool result = false;
	switch (i_position)
	{
	case InteractPosition::Front:
		if (boxToDog.CosineAngle2D(GetActorForwardVector()) >= 0.5f)
			result = true;
		break;
	case InteractPosition::Back:
		if (boxToDog.CosineAngle2D(-GetActorForwardVector()) >= 0.5f)
			result = true;
		break;
	case InteractPosition::Left:
		if (boxToDog.CosineAngle2D(-GetActorRightVector()) >= 0.5f)
			result = true;
		break;
	case InteractPosition::Right:
		if (boxToDog.CosineAngle2D(GetActorRightVector()) >= 0.5f)
			result = true;
		break;
	}
	return result;
}

void APushingBox::CheckInteractDirection()
{
	FCollisionShape shape = FCollisionShape::MakeBox(collider->GetScaledBoxExtent() * FVector(0.9f, 0.9f, 0.7f));
	TArray<FHitResult> sweepResults;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	FVector sweepEndPosition = GetActorLocation() + GetActorForwardVector() * (collider->GetScaledBoxExtent().X * 2 + 10.f);
	GetWorld()->SweepMultiByChannel(sweepResults, sweepEndPosition, sweepEndPosition, collider->GetComponentRotation().Quaternion(), ECC_Visibility, shape, params);
	for (auto& hit : sweepResults)
	{
		if (Cast<AABDogCharacter>(hit.Actor) && IsSameDirection(InteractPosition::Front))
		{
			myPushDirection = GetActorForwardVector();
			currentTrigger = trigger_front;
			interactTransform = trigger_front->GetComponentTransform();
			myInteractPosition = InteractPosition::Front;
		}
	}
	DrawDebugBox(GetWorld(), sweepEndPosition, shape.GetExtent(), collider->GetComponentRotation().Quaternion(), FColor::Red, false, 2.f);

	sweepResults.Empty();
	sweepEndPosition = GetActorLocation() - GetActorForwardVector() * (collider->GetScaledBoxExtent().X * 2 + 10.f);
	GetWorld()->SweepMultiByChannel(sweepResults, sweepEndPosition, sweepEndPosition, collider->GetComponentRotation().Quaternion(), ECC_Visibility, shape, params);
	for (auto& hit : sweepResults)
	{
		if (Cast<AABDogCharacter>(hit.Actor) && IsSameDirection(InteractPosition::Back))
		{
			myPushDirection = -GetActorForwardVector();
			currentTrigger = trigger_back;
			interactTransform = trigger_back->GetComponentTransform();
			myInteractPosition = InteractPosition::Back;
		}
	}
	DrawDebugBox(GetWorld(), sweepEndPosition, shape.GetExtent(), collider->GetComponentRotation().Quaternion(), FColor::Red, false, 2.f);

	sweepResults.Empty();
	sweepEndPosition = GetActorLocation() + GetActorRightVector() * (collider->GetScaledBoxExtent().Y * 2 + 10.f);
	GetWorld()->SweepMultiByChannel(sweepResults, sweepEndPosition, sweepEndPosition, collider->GetComponentRotation().Quaternion(), ECC_Visibility, shape, params);
	for (auto& hit : sweepResults)
	{
		if (Cast<AABDogCharacter>(hit.Actor) && IsSameDirection(InteractPosition::Right))
		{
			myPushDirection = GetActorRightVector();
			currentTrigger = trigger_right;
			interactTransform = trigger_right->GetComponentTransform();
			myInteractPosition = InteractPosition::Right;
		}
	}
	DrawDebugBox(GetWorld(), sweepEndPosition, shape.GetExtent(), collider->GetComponentRotation().Quaternion(), FColor::Red, false, 2.f);

	sweepResults.Empty();
	sweepEndPosition = GetActorLocation() - GetActorRightVector() * (collider->GetScaledBoxExtent().Y * 2 + 10.f);
	GetWorld()->SweepMultiByChannel(sweepResults, sweepEndPosition, sweepEndPosition, collider->GetComponentRotation().Quaternion(), ECC_Visibility, shape, params);
	for (auto& hit : sweepResults)
	{
		if (Cast<AABDogCharacter>(hit.Actor) && IsSameDirection(InteractPosition::Left))
		{
			myPushDirection = -GetActorRightVector();
			currentTrigger = trigger_left;
			interactTransform = trigger_left->GetComponentTransform();
			myInteractPosition = InteractPosition::Left;
		}
	}
	DrawDebugBox(GetWorld(), sweepEndPosition, shape.GetExtent(), collider->GetComponentRotation().Quaternion(), FColor::Red, false, 2.f);
	//if (GetWorld()->SweepSingleByChannel(
	//	sweepResult,
	//	sweepStartPosition,
	//	sweepStartPosition,
	//	collider->GetComponentRotation().Quaternion(),
	//	ECC_Visibility,
	//	shape,
	//	myCollisionParams))
}

void APushingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateBox();
	//if (bHeld && !isInPosition)
	//{
	//	auto character = GET_CHARACTER(InteractingComponent);
	//	AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
	//	if (dogCharacter)
	//	{
	//		// Lerp into push position
	//		float lerpProgress = FMath::Clamp(enterPositionTimer / enterPositionDuration, 0.f, 1.f);
	//		//FVector lerpPos = FMath::Lerp(characterTransform.GetLocation(), currentTrigger->GetComponentLocation(), lerpProgress);
	//		FRotator lerpRot = FMath::Lerp(characterTransform.GetRotation().Rotator(), currentTrigger->GetComponentRotation(), lerpProgress);
	//		//dogCharacter->SetActorLocation(lerpPos);
	//		dogCharacter->SetActorRotation(lerpRot.Quaternion());
	//		//dogCharacter->SetActorLocationAndRotation(lerpPos, lerpRot.Quaternion());
	//		enterPositionTimer += DeltaTime;

	//		if (lerpProgress >= 1.f)
	//		{
	//			enterPositionTimer = 0.f;
	//			isInPosition = true;
	//		}
	//	}
	//	
	//}

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
	// Collision shape for pushing box
	FCollisionShape shape = FCollisionShape::MakeBox(collider->GetScaledBoxExtent() * FVector(0.9f, 0.9f, 0.7f));
	FHitResult sweepResult;
	auto character = GET_CHARACTER(InteractingComponent);
	AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
	// if pulling, adjust the collision shape
	if (moveValue > 0.f)
	{
		// check interacting direction
		FVector boxExtent = collider->GetScaledBoxExtent();
		if (myInteractPosition == InteractPosition::Front || myInteractPosition == InteractPosition::Back)
			boxExtent.X = 30.f;
		else if (myInteractPosition == InteractPosition::Left || myInteractPosition == InteractPosition::Right)
			boxExtent.Y = 30.f;
			
		shape.MakeBox(boxExtent);
	}
	
	FVector sweepStartPosition = moveValue < 0.f ? GetActorLocation() : (dogCharacter->GetActorLocation() * FVector(1, 1, 0) + GetActorLocation() * FVector(0,0,1));
	FVector sweepEndPosition = moveValue < 0.f ?
		GetActorLocation() + (myPushDirection * collider->GetScaledBoxExtent() / 2 + myPushDirection * 20.f)
		: ((dogCharacter->GetActorLocation() ) * FVector(1,1,0) + GetActorLocation() * FVector(0, 0, 1)); // - currentTrigger->GetForwardVector() * 50.f

	DrawDebugBox(GetWorld(), sweepEndPosition, shape.GetExtent(), collider->GetComponentRotation().Quaternion(), FColor::Red);
	
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
		auto character = GET_CHARACTER(InteractingComponent);
		AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
		if (dogCharacter)
		{
			moveValue = -value;
			dogCharacter->myIsPulling = moveValue == 0.f ? false : true;
		}
			
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