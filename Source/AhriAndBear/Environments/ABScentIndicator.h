
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "ABScentIndicator.generated.h"

class USphereComponent;
class AABScentSource;

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
	void SetTargetPosition(FVector target);
	void SetIndicatorLifeSpan(float time);
	void MoveToTarget(float DeltaTime);

protected:
	virtual void BeginPlay() override;

public:	


private:
	USphereComponent* sensor;
	float lifeSpan;
	FVector targetPosition;
	FVector myVelocity;
	FVector mySteeringForce;
	BoidHelpler helper;
};


