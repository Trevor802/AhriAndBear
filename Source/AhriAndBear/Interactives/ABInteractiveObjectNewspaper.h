// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactives/Interactive.h"
#include "UI/NewspaperWidget.h"
#include "ABAnimalCharacter.h"
#include "Interactives/CharacterInteractionComponent.h"

#include "ABInteractiveObjectNewspaper.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API AABInteractiveObjectNewspaper : public AInteractive
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AABInteractiveObjectNewspaper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;

	virtual void CallMoveForward(float) override {};
	virtual void CallMoveRight(float value) override {};
	virtual void CallTurn(float value)override {};

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<class UNewspaperWidget> WidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		FString TempTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		int NewspaperIndex;
private:
	bool bOpened;

	class UNewspaperWidget* NewspaperWidget;

};
