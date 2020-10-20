// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interactive.h"
#include "ABInteractiveObjectBase.generated.h"

class AABAnimalCharacter;
UCLASS(Abstract)
class AHRIANDBEAR_API AABInteractiveObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABInteractiveObjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class AABAnimalCharacter* OverlappingAnimal;

	UFUNCTION() void OnEnterCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnExitCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	bool bCanBeInteracted;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool CanInteract() PURE_VIRTUAL(AABInteractiveObjectBase::CanInteract, return false;);
	virtual void Interact() PURE_VIRTUAL (AABInteractiveObjectBase::Interact,);
	virtual void AfterInteraction() PURE_VIRTUAL (AABInteractiveObjectBase::AfterInteraction,);

public:
	//virtual void AfterInteraction();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InteractionDelay;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UShapeComponent* CollisionShape;

};