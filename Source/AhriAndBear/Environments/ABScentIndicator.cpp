
#include "ABScentIndicator.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "ABScentSource.h"
#include "ABScentWaypoint.h"

AABScentIndicator::AABScentIndicator()
{
	sensor = CreateDefaultSubobject<USphereComponent>(TEXT("Unit Sensor"));
	sensor->SetupAttachment(RootComponent);
	sensor->SetSphereRadius(100);
	PrimaryActorTick.bCanEverTick = true;
	targetPosition = FVector::ZeroVector;
}

void AABScentIndicator::BeginPlay()
{
	Super::BeginPlay();	
}

void AABScentIndicator::CalculateDirection()
{
	if (!IsTargetReachable())
	{
		if(GetReachableWaypoint())
			SetTargetPosition(GetReachableWaypoint()->GetActorLocation());
	}
}

AABScentWaypoint* AABScentIndicator::GetReachableWaypoint()
{
	TArray<AActor*> overlappingActors;
	sensor->UpdateOverlaps();
	sensor->GetOverlappingActors(overlappingActors);
	if (overlappingActors.Num() == 0)
		return nullptr;
	else
	{
		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			if (!Cast<AABScentWaypoint>(overlappingActors[i]))
			{
				overlappingActors.RemoveAt(i);
				continue;
			}
			else
			{
				AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
				if (waypoint->isQueried)
					overlappingActors.RemoveAt(i);
			}
		}

		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
			if (waypoint->IsSourceReachable(mySource))
				return waypoint;
			else
			{
				AABScentWaypoint* nextReachable = waypoint->GetReachableWaypoint(mySource);
				if (nextReachable)
					return nextReachable;
			}
		}
	}
	return nullptr;
}

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

	DrawDebugSphere(GetWorld(), GetActorLocation(), 500, 4, FColor::Red);
	
	lifeSpan -= DeltaTime;
}

void AABScentIndicator::SetTargetPosition(FVector target)
{
	targetPosition = target;
}

void AABScentIndicator::SetTargetPosition(AABScentSource* target)
{
	mySource = target;
	targetPosition = target->GetActorLocation();
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

bool AABScentIndicator::IsTargetReachable()
{
	FHitResult onHit;
	FCollisionQueryParams CollisionParams;
	GetWorld()->LineTraceSingleByChannel(onHit,
		GetActorLocation(),
		targetPosition,
		ECollisionChannel::ECC_Visibility,
		CollisionParams);
	if (!Cast<AABScentSource>(onHit.GetActor()))
	{
		return false;
	}
	else
		return true;
}
