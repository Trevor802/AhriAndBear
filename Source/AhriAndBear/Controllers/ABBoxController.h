// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABPlayerController.h"
#include "ABBoxController.generated.h"

class AABInteractiveObjectBox;

UCLASS()
class AHRIANDBEAR_API AABBoxController : public AABPlayerController
{
	GENERATED_BODY()
	
public:
	AABBoxController();

	virtual void SetupInputComponent() override;

	void CallMoveForward(float value);
	void CallInteract();

	AABInteractiveObjectBox* boxControlled;
};
