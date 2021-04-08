#include "UI/ControllerWidgetSelectionItem.h"

void UABControllerWidgetSelectionItemFunctions::InvokeControllerWidgetEvent(const FControllerWidgetSelectionItem& item)
{
	item.buttonPressEvent.ExecuteIfBound();
}