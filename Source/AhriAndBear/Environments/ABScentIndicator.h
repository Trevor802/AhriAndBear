
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABScentIndicator.generated.h"

class USphereComponent;
class AABScentSource;

UCLASS()
class AHRIANDBEAR_API AABScentIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	AABScentIndicator();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	USphereComponent* sensor;
	FVector targetPosition;
	FVector myVelocity;
	FVector mySteeringForce;
};
