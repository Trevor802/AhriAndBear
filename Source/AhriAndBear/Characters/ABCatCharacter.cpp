// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCatCharacter.h"
#include "ABDogCharacter.h"
#include "ABPlayerController.h"

#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/PostProcessComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/Scene.h"

#include "Kismet/GameplayStatics.h"

AABCatCharacter::AABCatCharacter()
	: Super()
{
	postProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Process"));
	postProcess->bEnabled = true;
}

void AABCatCharacter::BeginPlay()
{
	Super::BeginPlay();
	abilityOn = false;
}

void AABCatCharacter::Tick(float DeltaTime)
{
	float currentAEMB = camera->PostProcessSettings.AutoExposureMinBrightness;
	if (abilityOn && currentAEMB < 1.0f)
	{
		camera->PostProcessSettings.AutoExposureMinBrightness += 0.1f * DeltaTime;
		if (camera->PostProcessSettings.AutoExposureMinBrightness > 1.0f)
		{
			camera->PostProcessSettings.AutoExposureMinBrightness = 1.0f;
			abilityOn = false;
		}
	}
}
		

void AABCatCharacter::UseAbility()
{
	Super::UseAbility();

	//UE_LOG(LogTemp, Warning, TEXT("???"));
	abilityOn = true;
	FPostProcessSettings NVsetting;
	NVsetting.bOverride_AutoExposureMinBrightness = true;
	NVsetting.bOverride_AutoExposureMaxBrightness = true;
	NVsetting.AutoExposureMinBrightness = 0.1f;
	NVsetting.AutoExposureMaxBrightness = 0.1f;

	camera->PostProcessSettings = NVsetting;
	AbilityEnd();
}

void AABCatCharacter::AbilityEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("???"));
	//abilityOn = false;
	camera->PostProcessSettings.AutoExposureMaxBrightness = 1.0f;
	/*FPostProcessSettings NormalSetting;
	NormalSetting.bOverride_AutoExposureMinBrightness = true;
	NormalSetting.bOverride_AutoExposureMaxBrightness = true;
	NormalSetting.AutoExposureMinBrightness = 1.0f;
	NormalSetting.AutoExposureMaxBrightness = 8.0f;

	camera->PostProcessSettings = NormalSetting;*/
}