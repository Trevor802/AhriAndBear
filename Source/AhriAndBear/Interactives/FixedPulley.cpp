// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPulley.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFixedPulley::AFixedPulley()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ActionHandler = CreateDefaultSubobject<USphereComponent>(TEXT("ActionHandler"));
	ActionHandler->SetupAttachment(RootComponent);
	ReactionHandler = CreateDefaultSubobject<USphereComponent>(TEXT("ReactionHandler"));
	ReactionHandler->SetupAttachment(RootComponent);

	ActionCable = CreateDefaultSubobject<UCableComponent>(TEXT("ActionCable"));
	ActionCable->SetupAttachment(RootComponent);
	ReactionCable = CreateDefaultSubobject<UCableComponent>(TEXT("ReactionCable"));
	ReactionCable->SetupAttachment(RootComponent);
	ActionCable->EndLocation = FVector::ZeroVector;
	ReactionCable->EndLocation = FVector::ZeroVector;
	ActionCable->SetAttachEndToComponent(ActionHandler);
	ReactionCable->SetAttachEndToComponent(ReactionHandler);	
	bCanBeInteracted = true;
	bCanAttachDog = false;
	bCanAttachCat = false;
	bAttachingDog = false;
	bAttachingCat = false;
}

void AFixedPulley::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (ReactionObject)
		ReactionObject->AttachToComponent(ReactionHandler, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	ActionCable->SetAttachEndToComponent(ActionHandler);
	ReactionCable->SetAttachEndToComponent(ReactionHandler);
}

// Called when the game starts or when spawned
void AFixedPulley::BeginPlay()
{
	Super::BeginPlay();
	ActionCable->SetAttachEndToComponent(ActionHandler);
	ReactionCable->SetAttachEndToComponent(ReactionHandler);
	if (ReactionObject)
		ReactionObject->AttachToComponent(ReactionHandler, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	TotalLength = ActionHandler->GetRelativeLocation().Size() + ReactionHandler->GetRelativeLocation().Size();
	ActionHandler->OnComponentBeginOverlap.AddDynamic(this, &AFixedPulley::OnStartOverlapBegin);
	ActionHandler->OnComponentEndOverlap.AddDynamic(this, &AFixedPulley::OnStartOverlapEnd);

	ReactionHandler->OnComponentBeginOverlap.AddDynamic(this, &AFixedPulley::OnEndOverlapBegin);
	ReactionHandler->OnComponentEndOverlap.AddDynamic(this, &AFixedPulley::OnEndOverlapEnd);
}

void AFixedPulley::AfterInteraction()
{
	if (Cast<AABDogCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (bAttachingDog == false && bCanAttachDog)
		{
			bAttachingDog = true;
		}
		else
		{
			bAttachingDog = false;
				bCanAttachDog = false;
		}
	}
	else if (Cast<AABCatCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (bAttachingCat == false && bCanAttachCat)
		{
			bAttachingCat = true;
		}
		else
		{
			bAttachingCat = false;
			bCanAttachCat = false;
		}
	}	
}

void AFixedPulley::OnStartOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<AABDogCharacter>(OtherActor))
	{
		bCanAttachDog = true;
		DogRef = Cast<AABDogCharacter>(OtherActor);
	}
}

void AFixedPulley::OnStartOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && Cast<AABDogCharacter>(OtherActor))
	{
		//bCanAttachDog = false;
	}
}

void AFixedPulley::OnEndOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<AABCatCharacter>(OtherActor))
	{
		bCanAttachCat = true;
		CatRef = Cast<AABCatCharacter>(OtherActor);
	}
}

void AFixedPulley::OnEndOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && Cast<AABCatCharacter>(OtherActor))
	{
		//bCanAttachCat = false;
	}
}

// Called every frame
void AFixedPulley::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHandlers();
}

void AFixedPulley::UpdateHandlers()
{
	float startLength = ActionHandler->GetRelativeLocation().Size();
	float endLength = FMath::Clamp(TotalLength - startLength, 10.0f, TotalLength / 2);
	ReactionHandler->SetRelativeLocation(FVector(0, 0, -1) * endLength);

	if (bAttachingDog && DogRef)
	{
		ActionHandler->SetWorldLocation(DogRef->GetActorLocation());
	}

	if (bAttachingCat && CatRef)
	{
		CatRef->SetActorLocation(ReactionHandler->GetComponentLocation());
	}
}

