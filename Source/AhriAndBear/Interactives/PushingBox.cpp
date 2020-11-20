// Fill out your copyright notice in the Description page of Project Settings.


#include "PushingBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Interactives/CharacterInteractionComponent.h"
#include "ABAnimalCharacter.h"
#include "ABPlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Characters/ABDogCharacter.h"

APushingBox::APushingBox()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	boxMesh->SetupAttachment(RootComponent);
	

	trigger_h = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Horizontal"));
	trigger_h->SetBoxExtent(FVector(60, 2, 20));
	trigger_h->SetupAttachment(boxMesh);
	trigger_h->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::h_OnOverlapBegin);
	trigger_h->OnComponentEndOverlap.AddDynamic(this, &APushingBox::h_OnOverlapEnd);

	trigger_v = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Vertical"));
	trigger_v->SetBoxExtent(FVector(2, 60, 20));
	trigger_v->SetupAttachment(boxMesh);
	trigger_v->OnComponentBeginOverlap.AddDynamic(this, &APushingBox::v_OnOverlapBegin);
	trigger_v->OnComponentEndOverlap.AddDynamic(this, &APushingBox::v_OnOverlapEnd);
}

void APushingBox::BeginPlay()
{
	horizontal = false;
	verticle = false;
	boxMesh->GetBodyInstance()->bLockXRotation = true;
	boxMesh->GetBodyInstance()->bLockYRotation = true;
	boxMesh->GetBodyInstance()->bLockZRotation = true;

	LockMeshLocation();
}

void APushingBox::BeginInteraction()
{
	
	auto character = GET_CHARACTER(InteractingComponent);
	AABDogCharacter* dogCharacter = Cast<AABDogCharacter>(character);
	if (dogCharacter)
	{
		//SetBoxOverlap(true);
		//boxMesh->SetSimulatePhysics(true);
		if (horizontal)
		{
			boxMesh->GetBodyInstance()->bLockYTranslation = false;
		}
		else if (verticle)
		{
			boxMesh->GetBodyInstance()->bLockXTranslation = false;
		}

		AttachToComponent(character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	}

}

void APushingBox::EndInteraction(bool)
{
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	
	LockMeshLocation();
	//boxMesh->IgnoreActorWhenMoving(character, false);
	//SetBoxOverlap(false);
}

void APushingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UpdateBox();
}

void APushingBox::UpdateBox()
{
	
}

void APushingBox::CallMoveForward(float value)
{
	Super::CallMoveForward(value);
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

void APushingBox::h_OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("H True"));
		horizontal = true;
	}
}

void APushingBox::v_OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("V True"));
		verticle = true;
	}
}

void APushingBox::h_OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("H false"));
		horizontal = false;
	}
}

void APushingBox::v_OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("V false"));
		verticle = false;
	}
}

void APushingBox::LockMeshLocation()
{
	
	boxMesh->GetBodyInstance()->bLockZTranslation = true;
	boxMesh->GetBodyInstance()->bLockYTranslation = true;
	boxMesh->GetBodyInstance()->bLockXTranslation = true;
	boxMesh->SetSimulatePhysics(false);
}