// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CharacterInteractionComponent.generated.h"

class AABInteractiveObjectBase;
DECLARE_MULTICAST_DELEGATE(FInteractionStopped);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UCharacterInteractionComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterInteractionComponent();
	FORCEINLINE void SetOccupying(bool occupying) { bOccupying = occupying; }
	FORCEINLINE void SetMouthInteracting(bool interacting) { bMouthInteracting = interacting; }
	FORCEINLINE void SetPawInteracting(bool interacting) { bPawInteracting = interacting; }
	FORCEINLINE bool IsOccupying() const { return bOccupying; }
	FORCEINLINE bool IsMouthInteracting() const { return bMouthInteracting; }
	FORCEINLINE bool IsPawInteracting() const { return bPawInteracting; }
	bool TryInteracting();
	FInteractionStopped OnInteractionStopped;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bOccupying;
	bool bMouthInteracting;
	bool bPawInteracting;
	TArray<AABInteractiveObjectBase*> SortInteractives(const TArray<AABInteractiveObjectBase*>& interactives) const;
};
