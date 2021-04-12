#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControllerWidgetSelectionItem.h"
#include "GamepadCompatibleWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMenuSelectionChanged, const FControllerWidgetSelectionItem&, OldSelection, const FControllerWidgetSelectionItem&, CurrentSelection);

/**
 * Represents a widget that can interface with a controller. Also provides keyboard support.
 */
UCLASS()
class AHRIANDBEAR_API UGamepadCompatibleWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/**
	* Triggered whenever a horizontal joystick axis input is detected.
	*
	* @param value
	*   The value of the joystick axis input.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Input")
		void UIHorizontalSelectionChanged(float value);

	/**
	* Triggered whenever a vertical joystick axis input is detected.
	*
	* @param value
	*   The value of the joystick axis input.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Input")
		void UIVerticalSelectionChanged(float value);

	/**
	* Triggered whenever the confirm input action is detected.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Input")
		void UIConfirmPressed();

	/**
	* Triggered whenever the cancel input action is detected.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Input")
		void UICancelPressed();

protected:
	// Protected methods
	/**
	* Registers a button that can be selected by the gamepad.
	*
	* @param item
	*   The item that can be selected by the gamepad.
	*/
	UFUNCTION(BlueprintCallable, Category = "UI|Input")
		void RegisterButton(const FControllerWidgetSelectionItem& item);

	/**
	* Advances the current selection based on the sign of direction.
	*
	* @param direction
	*   Decreases the current selection index by 1 if negative; if positive, increases the current selection by 1. If zero, no change.
	*/
	UFUNCTION(BlueprintCallable, Category = "UI|Input")
		void AdvanceSelection(float direction);

	/**
	* DEPRECATED. Will be removed after I compile successfully with blueprints.
	* 
	* @see AdvanceSelection
	*/
	UFUNCTION(meta=(DeprecatedFunction, DeprecationMessage="Use AdvanceSelection instead."), BlueprintCallable, Category = "UI|Input")
		void ChangeSelection(float selectionDirectionChanged);

	/**
	* Retrieves the current selection index.
	*
	* @return
	*   The index of the currently selected item.
	*/
	UFUNCTION(BlueprintPure, Category="UI|Input")
		int GetCurrentSelectionIndex() const { return currentSelectionIndex; }

	/**
	* Changes the current selection index to the provided index.
	*
	* @param index
	*   The new index. If the index is invalid, will silently fail.
	*/
	UFUNCTION(BlueprintCallable, Category = "UI|Input")
		void ChangeMenuSelection(int index, bool triggerEvent);
	
	/**
	* Retrieves the currently selected item.
	*
	* @return
	*   The currently selected item.
	*/
	UFUNCTION(BlueprintPure, Category="UI|Input")
		const FControllerWidgetSelectionItem& GetCurrentlySelectedItem() const { return widgetItems[currentSelectionIndex]; }

	// Protected properties
	/**
	* Triggered whenever the current index is changed.
	*
	* @see ChangeMenuSelection
	* @see AdvanceSelection
	*/
	UPROPERTY(BlueprintAssignable, Category = "UI|Input")
		FMenuSelectionChanged OnMenuSelectionChanged;

private:
	TArray<FControllerWidgetSelectionItem> widgetItems;
	int currentSelectionIndex = 0;
};
