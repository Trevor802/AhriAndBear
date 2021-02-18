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

AABScentWaypoint* AABScentWaypoint::GetReachableWaypoint(AABScentSource* targetSource, TArray<FVector>& i_pathNodes)
{
	if (isQueried)
		return nullptr;

	TArray<AActor*> overlappingActors;
	waypointCollider->UpdateOverlaps();
	waypointCollider->GetOverlappingActors(overlappingActors, AABScentWaypoint::StaticClass());
	isQueried = true;
	if (overlappingActors.Num() == 0)
		return nullptr;
	else
	{
		//for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		//{
		//	AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
		//	if(waypoint->isQueried)
		//		overlappingActors.RemoveAt(i);
		//}
		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
			if (waypoint == this || waypoint->isQueried)
				overlappingActors.RemoveAt(i);
		}

		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
			if (waypoint->IsSourceReachable(targetSource))
			{
				i_pathNodes.Add(waypoint->GetActorLocation());
				return waypoint;
			}
				
		}

		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
			AABScentWaypoint* nextReachable = waypoint->GetReachableWaypoint(targetSource, i_pathNodes);
			if (nextReachable)
				return nextReachable;
		}
	}
	return nullptr;
}

bool AABScentWaypoint::IsSourceReachable(AABScentSource* targetSource)
{
	FHitResult onHit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(onHit,
		GetActorLocation(),
		targetSource->GetActorLocation(),
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

