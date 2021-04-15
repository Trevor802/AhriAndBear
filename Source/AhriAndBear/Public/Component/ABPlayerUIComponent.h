// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/InteractionDurationWidget.h"
#include "UI/NewspaperWidget.h"
#include "UI/HintWidget.h"
#include "UI/InteractiveHintWidget.h"
#include "UI/EndWidget.h"
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
	void InitNewsWidget();
	void InitHintWidget();
	void InitInteractiveHintWidget();
	void InitEndWidget();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddNewspaperWidgetToViewPort();
	void RemoveNewspaperWidgetFromViewPort();

	void AddHintWidgetToViewPort();
	void CheckHintUI();
	void HideHintUI();

	void AddInteractiveHintWidgetToViewPort();
	void CheckInteractiveHintUI();
	void HideInteractiveHintUI();

	void AddEndWidgetToViewPort();
	void CheckEndWidget();

private:
	AABPlayerController* PlayerController;
	AABAnimalCharacter* character;

	bool bHintWidgetShowed;
	bool bInteractiveHintWidgetShowed;
	bool bEndWidgetShowed;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<class UNewspaperWidget> NewspaperWidgetClass;
	class UNewspaperWidget* NewspaperWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<class UHintWidget> HintWidgetClass;
	class UHintWidget* HintWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<class UInteractiveHintWidget> IntreactiveHintWidgetClass;
	class UInteractiveHintWidget* InteractiveHintWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<class UEndWidget> EndWidgetClass;
	class UEndWidget* EndWidget;

protected:
	FTimerHandle TimerHandle;
};
