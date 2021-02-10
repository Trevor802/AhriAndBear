// Fill out your copyright notice in the Description page of Project Settings.


#include "Environments/ABScentWaypoint.h"
#include "Components/SphereComponent.h"
#include "ABScentIndicator.h"
#include "ABScentSource.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"

AABScentWaypoint::AABScentWaypoint()
{
	PrimaryActorTick.bCanEverTick = false;
	waypointCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	waypointCollider->SetupAttachment(RootComponent);
}

void AABScentWaypoint::BeginPlay()
{
	Super::BeginPlay();
}

AABScentWaypoint* AABScentWaypoint::GetReachableWaypoint(AABScentSource* targetSource)
{
	TArray<AActor*> overlappingActors;
	waypointCollider->UpdateOverlaps();
	waypointCollider->GetOverlappingActors(overlappingActors);
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
				if(waypoint->isQueried)
					overlappingActors.RemoveAt(i);
			}
		}

		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
			if (waypoint->IsSourceReachable(targetSource))
				return waypoint;
			else
			{
				AABScentWaypoint* nextReachable = waypoint->GetReachableWaypoint(targetSource);
				if (nextReachable)
					return nextReachable;
			}
		}
	}
	return nullptr;
}

bool AABScentWaypoint::IsSourceReachable(AABScentSource* targetSource)
{
	FVector toTarget = targetSource->GetActorLocation() - GetActorLocation();
	FHitResult onHit;
	FCollisionQueryParams CollisionParams;
	GetWorld()->LineTraceSingleByChannel(onHit,
		GetActorLocation(),
		GetActorLocation() + toTarget,
		ECollisionChannel::ECC_WorldDynamic,
		CollisionParams);
	if (!Cast<AABScentSource>(onHit.GetActor()))
	{
		return false;
	}
	else
		return true;

}

void AABScentWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

