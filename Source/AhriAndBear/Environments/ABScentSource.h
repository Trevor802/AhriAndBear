 // The improved scent trail that is supposed to be like Scoutflies in Monster Hunter World
// The source of scent.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABScentSource.generated.h"

class AABDogCharacter;
class USphereComponent;

UCLASS()
class AHRIANDBEAR_API AABScentSource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABScentSource();
	bool GetIsDogInRange();
	void SetDogInRange(bool);
	UFUNCTION()
	void PlayerCharacterInRange(AActor* self, AActor* OtherActor);
	UFUNCTION()
	void PlayerCharacterOutRange(AActor* self, AActor* OtherActor);
	void SpawnScentIndicator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		USphereComponent* scentRangeSphere;

private:
	AABDogCharacter* dogInRange;
	bool isDogInRange;
	
};
