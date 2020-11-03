// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABStatModifierInterface.generated.h"

// Forward declares
class AABSurvivalComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UABStatModifierInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AHRIANDBEAR_API IABStatModifierInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	int GetMaxHungerModifier(AABSurvivalComponent* mainComp) PURE_VIRTUAL(":D", return 0;);
	int GetHungerRateModifier(AABSurvivalComponent* mainComp) PURE_VIRTUAL("Or do I need text", return 0;);

	int GetMaxThirstModifier(AABSurvivalComponent* mainComp) PURE_VIRTUAL("Compile", return 0;);

	int GetThirstRateModifier(AABSurvivalComponent* mainComp) PURE_VIRTUAL("Hmm", return 0;);
};
