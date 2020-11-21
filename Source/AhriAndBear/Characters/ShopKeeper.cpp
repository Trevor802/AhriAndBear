// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopKeeper.h"
#include "ABAnimalCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AShopKeeper::AShopKeeper()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);

	Box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box1"));
	Box1->SetupAttachment(RootComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShopKeeper::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AShopKeeper::OnBoxBeginOverlap);
	Box1->OnComponentBeginOverlap.AddDynamic(this, &AShopKeeper::OnBox1BeginOverlap);
}

// Called every frame
void AShopKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShopKeeper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AShopKeeper::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AABAnimalCharacter* animal = Cast<AABAnimalCharacter>(OtherActor);
	if (animal != nullptr) {
		animal->GetCaught(this);
	}
}

void AShopKeeper::OnBox1BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AABAnimalCharacter* animal = Cast<AABAnimalCharacter>(OtherActor);
	if (animal != nullptr) {
		animal->GetCaught(this);
	}
}
TArray<AActor*> AShopKeeper::GetPatrolPositions()
{
	return PatrolPositions;
}
