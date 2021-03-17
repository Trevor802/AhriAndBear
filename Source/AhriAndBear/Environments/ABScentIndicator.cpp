
#include "ABScentIndicator.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "ABScentSource.h"
#include "ABScentWaypoint.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

AABScentIndicator::AABScentIndicator()
{
	sensor = CreateDefaultSubobject<USphereComponent>(TEXT("Unit Sensor"));
	sensor->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
	targetPosition = FVector::ZeroVector;
	myTrailComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail Comp"));
	myTrailComponent->SetupAttachment(RootComponent);
	stuckTimer = 3.f;
}

void AABScentIndicator::BeginPlay()
{
	Super::BeginPlay();
	lastFrameLocation = GetActorLocation();
	//myTrailComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), trailVFX, GetActorLocation(), FRotator::ZeroRotator, (FVector)1.0f, false);
	//myTrailComponent->Activate(true);
}

void AABScentIndicator::CalculateDirection()
{
	if (!IsTargetReachable())
	{
		if (GetReachableWaypoint())
		{
			myCurrentPathNode = myPathNodes.Num() - 1;
			targetPosition = myPathNodes[myCurrentPathNode];
			SetTargetPosition(targetPosition);
			//SetTargetPosition(GetReachableWaypoint()->GetActorLocation());
		}
			
	}
}

AABScentWaypoint* AABScentIndicator::GetReachableWaypoint()
{
	TArray<AActor*> overlappingActors;
	sensor->SetSphereRadius(scanRange);
	sensor->UpdateOverlaps();
	sensor->GetOverlappingActors(overlappingActors, AABScentWaypoint::StaticClass());
	if (overlappingActors.Num() == 0)
		return nullptr;
	else
	{
		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
			if (!IsWaypointReachable(waypoint))
			{
				overlappingActors.RemoveAt(i);
				continue;
			}
				
			if (waypoint)
				waypoint->isQueried = false;
		}
		overlappingActors.Sort([this](const AActor& lhs, const AActor& rhs) {
			return lhs.GetDistanceTo(this) > rhs.GetDistanceTo(this); });

		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
			if (waypoint->IsSourceReachable(mySource))
			{
				myPathNodes.Add(waypoint->GetActorLocation());
				return waypoint;
			}
				
		}
		
		for (int i = overlappingActors.Num() - 1; i >= 0; i--)
		{
			AABScentWaypoint* waypoint = Cast<AABScentWaypoint>(overlappingActors[i]);
			AABScentWaypoint* nextReachable = waypoint->GetReachableWaypoint(mySource, myPathNodes);
			if (nextReachable)
			{
				myPathNodes.Add(waypoint->GetActorLocation());
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
	{
		myTrailComponent->DestroyComponent();
		Destroy();
	}
		

	MoveToTarget(DeltaTime);

	//for (int i = 0; i < helper.G_S_directions.Num(); i++)
	//{
	//	DrawDebugLine(GetWorld(),
	//		GetActorLocation(),
	//		GetActorLocation() + helper.G_S_directions[i] * 30,
	//		FColor::Red);
	//}

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 500, 4, FColor::Red);
	if (myReachingTarget)
	{
		lifeSpan -= DeltaTime;
	}

	if (lifeSpan <= 0.f)
		Destroy();
}

void AABScentIndicator::SetTargetPosition(FVector target)
{
	targetPosition = target;
	myPathNodes.Add(target);
}

void AABScentIndicator::SetTargetPosition(AABScentSource* target)
{
	mySource = target;
	targetPosition = target->GetActorLocation();
	myPathNodes.Add(target->GetActorLocation());
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
	lastFrameLocation = GetActorLocation();
	FVector updatedLocation = GetActorLocation() + myVelocity * DeltaTime;
	SetActorLocation(updatedLocation);

	if (FVector::Distance(targetPosition, GetActorLocation()) <= myReachingRange)
	{
		if (myCurrentPathNode - 1 >= 0)
		{
			myCurrentPathNode--;
			SetTargetPosition(myPathNodes[myCurrentPathNode]);
		}
		else
			myReachingTarget = true;
	}

	if (FVector::Distance(updatedLocation, lastFrameLocation) < 100.f * DeltaTime)
	{
		stuckTimer -= DeltaTime;
		if (stuckTimer <= 0.f)
			lifeSpan = 0.f;
	}
}

bool AABScentIndicator::IsWaypointReachable(const AABScentWaypoint* actor)
{
	FHitResult onHit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(onHit,
		GetActorLocation(),
		actor->GetActorLocation(),
		ECollisionChannel::ECC_WorldDynamic,
		CollisionParams);
	if (!Cast<AABScentWaypoint>(onHit.GetActor()))
	{
		return false;
	}
	else
		return true;
}

bool AABScentIndicator::IsTargetReachable()
{
	FHitResult onHit;
	//TArray<FHitResult> hits;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	//GetWorld()->LineTraceMultiByChannel(hits,
	//	GetActorLocation(),
	//	targetPosition,
	//	ECollisionChannel::ECC_WorldDynamic,
	//	CollisionParams);
	GetWorld()->LineTraceSingleByChannel(onHit,
		GetActorLocation(),
		targetPosition,
		ECollisionChannel::ECC_WorldDynamic,
		CollisionParams);
	//for (int i = hits.Num(); i >= 0; i--)
	//{
	//	if (Cast<AABDogCharacter>(hits[i].GetActor()) || Cast<AABCatCharacter>(hits[i].GetActor()))
	//		;
	//}
	if (!Cast<AABScentSource>(onHit.GetActor()))
	{
		return false;
	}
	else
		return true;
}
