// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/OccupyingInteractive.h"
#include "ABInteractiveObjectNewspaper.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectNewspaper : public AOccupyingInteractive
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AABInteractiveObjectNewspaper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent* component) const override { return !bOpened; }
	virtual void EndInteraction(bool) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void OpenNewspaper();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* CollisionShape;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* NewspaperMesh;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		class UWidget* NewspaperWidget;
		*/
private:
	bool bOpened;



};
