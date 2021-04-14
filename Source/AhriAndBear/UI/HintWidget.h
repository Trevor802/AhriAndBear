

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HintWidget.generated.h"

/**
 * 
 */
UCLASS()
class AHRIANDBEAR_API UHintWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void ShowHint(float Duration);
	UFUNCTION(BlueprintImplementableEvent)
		void HideHint();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FString HintString;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		bool bShowing = false;
};
