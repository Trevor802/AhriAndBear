// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Interactive.h"
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
	UFUNCTION() void OnEnterCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) { bCanInteract = true; }
	UFUNCTION() void OnExitCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) { bCanInteract = false; }

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UShapeComponent* CollisionShape;

private:
	bool bCanInteract;
};
