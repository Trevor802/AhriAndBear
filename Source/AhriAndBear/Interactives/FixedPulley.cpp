// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPulley.h"
#include "Components/SphereComponent.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values
AFixedPulley::AFixedPulley()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Start = CreateDefaultSubobject<USphereComponent>(TEXT("Start"));
	Start->SetupAttachment(RootComponent);
	End = CreateDefaultSubobject<USphereComponent>(TEXT("End"));
	End->SetupAttachment(RootComponent);
	CableStart = CreateDefaultSubobject<UCableComponent>(TEXT("CalbeStart"));
	CableStart->SetupAttachment(RootComponent);
	CableStart->EndLocation = FVector::ZeroVector;
	CableEnd = CreateDefaultSubobject<UCableComponent>(TEXT("CalbeEnd"));
	CableEnd->SetupAttachment(RootComponent);
	CableEnd->EndLocation = FVector::ZeroVector;
	Start->SetRelativeLocation(FVector(0, 0, -1) * TotalLength / 2);
	End->SetRelativeLocation(FVector(0, 0, -1) * TotalLength / 2);

	bCanBeInteracted = true;
	bCanAttachDog = false;
	bCanAttachCat = false;
	bAttachingDog = false;
	bAttachingCat = false;
}

// Called when the game starts or when spawned
void AFixedPulley::BeginPlay()
{
	Super::BeginPlay();
	
	CableStart->SetAttachEndToComponent(Start);
	CableEnd->SetAttachEndToComponent(End);

	Start->OnComponentBeginOverlap.AddDynamic(this, &AFixedPulley::OnStartOverlapBegin);
	Start->OnComponentEndOverlap.AddDynamic(this, &AFixedPulley::OnStartOverlapEnd);

	End->OnComponentBeginOverlap.AddDynamic(this, &AFixedPulley::OnEndOverlapBegin);
	End->OnComponentEndOverlap.AddDynamic(this, &AFixedPulley::OnEndOverlapEnd);
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
	float startLength = Start->GetRelativeLocation().Size();
	float endLength = FMath::Clamp(TotalLength - startLength, 10.0f, TotalLength / 2);
	CableEnd->CableLength = endLength;
	End->SetRelativeLocation(FVector(0, 0, -1) * endLength);

	if (bAttachingDog && DogRef)
	{
		Start->SetWorldLocation(DogRef->GetActorLocation());
	}

	if (bAttachingCat && CatRef)
	{
		CatRef->SetActorLocation(End->GetComponentLocation());
	}
}

