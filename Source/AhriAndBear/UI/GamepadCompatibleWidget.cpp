#include "UI/GamepadCompatibleWidget.h"
#include "GamepadCompatibleWidget.h"

void UGamepadCompatibleWidget::UIHorizontalSelectionChanged_Implementation(float value) {}

void UGamepadCompatibleWidget::UIVerticalSelectionChanged_Implementation(float value) {}

void UGamepadCompatibleWidget::UIConfirmPressed_Implementation() {}

void UGamepadCompatibleWidget::UICancelPressed_Implementation() {}

void UGamepadCompatibleWidget::RegisterButton(const FControllerWidgetSelectionItem& item) {
	widgetItems.Add(item);
}

void UGamepadCompatibleWidget::AdvanceSelection(float direction)
{
	if (widgetItems.Num() == 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No widget items have been registered."));
		return;
	}
	else if (direction == 0.f) {
		return;
	}
	// Cache old selected index for later
	int oldSelectedIndex = currentSelectionIndex;

	int value = FMath::TruncToInt(FMath::Sign(direction));
	currentSelectionIndex += value;
	// This will cause values > widgetItems.Num() to roll back to zero and a
	// value < 0 to roll over to widgetItems.Num() - 1.
	currentSelectionIndex = (currentSelectionIndex + widgetItems.Num()) % widgetItems.Num();

	OnMenuSelectionChanged.Broadcast(widgetItems[oldSelectedIndex], widgetItems[currentSelectionIndex]);
}

void UGamepadCompatibleWidget::ChangeSelection(float value)
{
	AdvanceSelection(value);
}

void UGamepadCompatibleWidget::ChangeMenuSelection(int index, bool triggerEvent)
{
	if (!widgetItems.IsValidIndex(index)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid index provided"));
		return;
	}
	else if (index == currentSelectionIndex) {
		return;
	}

	int oldIndex = currentSelectionIndex;
	int currentSelectionIndex = index;

	if (triggerEvent)
		OnMenuSelectionChanged.Broadcast(widgetItems[oldIndex], widgetItems[currentSelectionIndex]);
}
