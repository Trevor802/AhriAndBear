
#include "ABScentIndicator.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

// Sets default values
AABScentIndicator::AABScentIndicator()
{
	sensor = CreateDefaultSubobject<USphereComponent>(TEXT("Unit Sensor"));
	sensor->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
	targetPosition = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AABScentIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABScentIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (lifeSpan <= 0)
		Destroy();

	MoveToTarget(DeltaTime);

	for (int i = 0; i < helper.G_S_directions.Num(); i++)
	{
		DrawDebugLine(GetWorld(),
			GetActorLocation(),
			GetActorLocation() + helper.G_S_directions[i] * 30,
			FColor::Red);
	}
	
	lifeSpan -= DeltaTime;
}

void AABScentIndicator::SetTargetPosition(FVector target)
{
	targetPosition = target;
}

void AABScentIndicator::SetIndicatorLifeSpan(float time)
{
	lifeSpan = time;
}

void AABScentIndicator::MoveToTarget(float DeltaTime)
{
	FVector toTarget = targetPosition - GetActorLocation();
	FVector arrival = FVector::ZeroVector;
	FVector avoid = FVector::ZeroVector;
	arrival = toTarget.GetSafeNormal();
	for (int i = 0; i < helper.G_S_directions.Num(); i++)
	{
		FHitResult onHit;
		FCollisionQueryParams CollisionParams;
		if (GetWorld()->LineTraceSingleByChannel(onHit,
			GetActorLocation(),
			GetActorLocation() + helper.G_S_directions[i] * 30,
			ECollisionChannel::ECC_Visibility,
			CollisionParams))
		{
			avoid += -helper.G_S_directions[i].GetSafeNormal();
		}
	}
	myVelocity = (arrival + avoid).GetSafeNormal() * 100;
	SetActorLocation(GetActorLocation() + myVelocity * DeltaTime);
}
