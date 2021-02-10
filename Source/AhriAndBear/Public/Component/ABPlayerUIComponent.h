// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/InteractionDurationWidget.h"
#include "UI/NewspaperWidget.h"
#include "ABPlayerController.h"
#include "ABAnimalCharacter.h"
#include "ABPlayerUIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AHRIANDBEAR_API UABPlayerUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABPlayerUIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void InitWidgets();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CallAddWidgetToViewPort(UUserWidget* Widget);
	void CallRemoveWidgetFromViewPort(UUserWidget* Widget);

private:
	AABPlayerController* PlayerController;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<class UNewspaperWidget> NewspaperWidgetClass;
	class UNewspaperWidget* NewspaperWidget;
};
