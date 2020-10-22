// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactive.h"
#include "ABInteractiveObjectBase.generated.h"

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
	virtual void OnActorEnter(AActor* OtherActor) {};
	virtual void OnActorExit(AActor* OtherActor) {};
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UShapeComponent* CollisionShape;
	class UEventTrigger* EventTrigger;

public:	

	bool CanInteract();

	virtual void Tick(float DeltaTime) override;
	virtual void Interact() PURE_VIRTUAL (AABInteractiveObjectBase::Interact,);
	virtual void AfterInteraction() PURE_VIRTUAL (AABInteractiveObjectBase::AfterInteraction,);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	float InteractionDelay;


};