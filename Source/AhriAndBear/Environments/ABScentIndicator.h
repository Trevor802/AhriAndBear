
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "ABScentIndicator.generated.h"

class USphereComponent;
class AABScentSource;
class AABScentWaypoint;
class AABCatCharacter;
class UNiagaraSystem;
class UNiagaraComponent;

// Stolen from Trevor's research project
static class BoidHelpler
{
public:
	TArray<FVector> G_S_directions;
	BoidHelpler()
	{
		float goldenRatio = (1 + sqrt(5)) / 2;
		float _1 = 1.f / num_Directions * 2.f;
		float angleInc = PI * 2 * goldenRatio;
		for (int i = 0; i < num_Directions; i++)
		{
			float pitch = acosf(1 - i * _1);
			float roll = angleInc * i;
			float x = sinf(pitch) * cosf(roll);
			float y = sinf(pitch) * sinf(roll);
			float z = cosf(pitch);
			G_S_directions.Add(FVector(x, y, z));
		}
	}
private:
	const int num_Directions = 20;
};

UCLASS()
class AHRIANDBEAR_API AABScentIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	AABScentIndicator();
	virtual void Tick(float DeltaTime) override;
	void InitIndicator(AABScentSource* targetSource);
	void SetTargetPosition(FVector target);
	void SetTargetPosition(AABScentSource* targetSource);
	void SetIndicatorLifeSpan(float time);
	void MoveToTarget(float DeltaTime);
	bool IsTargetReachable();
	bool IsWaypointReachable(const AABScentWaypoint*);
	AABScentWaypoint* GetReachableWaypoint();
	void CalculateDirection();
	void SetNextWaypoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		USphereComponent* sensor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float scanRange = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Property")
		UNiagaraSystem* trailVFX;

protected:
	virtual void BeginPlay() override;

private:
	TArray<FVector> myPathNodes;
	AABScentSource* mySource;
	float lifeSpan;
	FVector targetPosition;
	FVector myVelocity;
	FVector mySteeringForce;
	BoidHelpler helper;
	bool myReachingTarget;
	float myReachingRange = 30.f;
	int myCurrentPathNode = 0;
	UNiagaraComponent* myTrailComponent;
};


