// Fill out your copyright notice in the Description page of Project Settings.


#include "ABBoxController.h"
#include "GameFramework/Actor.h"
#include "Interactives/ABInteractiveObjectBox.h"

AABBoxController::AABBoxController() : Super()
{

}

void AABBoxController::SetupInputComponent()
{
	//Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAxis("WalkForward", this, &AABBoxController::CallMoveForward);

	InputComponent->BindAction("Catch", IE_Pressed, this, &AABBoxController::CallInteract);

}

void AABBoxController::CallMoveForward(float value)
{
	if (boxControlled)
	{
		boxControlled->AddForceAlongAxis(value);
	}
}

void AABBoxController::CallInteract()
{

}