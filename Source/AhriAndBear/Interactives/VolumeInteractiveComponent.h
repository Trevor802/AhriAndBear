// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Interactive.h"
#include "GameBase/Define.h"
#include "ABAnimalCharacter.h"
#include "VolumeInteractiveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UVolumeInteractiveComponent : public UActorComponent, public IInteractive
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVolumeInteractiveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION() void OnEnterCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnExitCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void SaveGame(AABAnimalCharacter*) const;
	void LoadLevel(ELevelName) const;
	void ChangeWarmthRate(AABAnimalCharacter*, float);
	void Supply(const FSurvivalData&);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UShapeComponent* CollisionShape;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FEventData EventData;
	FORCEINLINE bool CanInteractive() const { return bCanInteract; }
	void Interact();
private:
	AABAnimalCharacter* AnimalOverlapping = nullptr;
	bool bCanInteract;
	float OldWarmthRate;
};
