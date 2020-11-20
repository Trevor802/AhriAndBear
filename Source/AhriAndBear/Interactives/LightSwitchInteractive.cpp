// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitchInteractive.h"
#include "Engine/Light.h"

void ALightSwitchInteractive::BeginPlay()
{
	Super::BeginPlay();
	SwitchAllLights(bDefaultOn);
}

void ALightSwitchInteractive::EndInteraction(bool bInResult)
{
	if (bInResult)
	{
		SwitchAllLights(!bCurrentOn);
	}
	Super::EndInteraction(bInResult);
}

void ALightSwitchInteractive::SwitchAllLights(bool bInOn)
{
	for(auto& light : Lights)
	{
		light->SetEnabled(bInOn);
	}
	bCurrentOn = bInOn;
}
