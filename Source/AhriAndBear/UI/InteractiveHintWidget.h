

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveHintWidget.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API UInteractiveHintWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent)
		void ShowHint();
	UFUNCTION(BlueprintImplementableEvent)
		void HideHint();
};
