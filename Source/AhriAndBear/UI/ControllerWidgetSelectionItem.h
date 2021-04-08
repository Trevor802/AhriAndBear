

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"

#include "ControllerWidgetSelectionItem.generated.h"

DECLARE_DYNAMIC_DELEGATE(FUIButtonPressed);

/**
 * 
 */
USTRUCT(BlueprintType)
struct AHRIANDBEAR_API FControllerWidgetSelectionItem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category="UI|Input")
	UButton* button;

	UPROPERTY(BlueprintReadWrite, Category = "UI|Input")
	FUIButtonPressed buttonPressEvent;
};

UCLASS()
class AHRIANDBEAR_API UABControllerWidgetSelectionItemFunctions :
	public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "UI|Input")
		static void InvokeControllerWidgetEvent(const FControllerWidgetSelectionItem& item);
};
