#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamepadCompatibleWidget.generated.h"

/**
 * Represents a widget that can interface with a controller. Also provides keyboard support.
 */
UCLASS()
class AHRIANDBEAR_API UGamepadCompatibleWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Input")
		void UIHorizontalSelectionChanged(float value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Input")
		void UIVerticalSelectionChanged(float value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Input")
		void UIConfirmPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Input")
		void UICancelPressed();
};
