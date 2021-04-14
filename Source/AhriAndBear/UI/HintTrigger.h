

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ABAnimalCharacter.h"
#include "HintTrigger.generated.h"

UCLASS()
class AHRIANDBEAR_API AHintTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHintTrigger();

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString TriggerHintString = "";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bTriggered = false;

};
