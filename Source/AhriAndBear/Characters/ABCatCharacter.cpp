// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCatCharacter.h"
#include "ABDogCharacter.h"
#include "ABPlayerController.h"

#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"
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
	Super::Tick(DeltaTime);

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
	FPostProcessSettings NVsetting;
	if (!abilityOn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("???"));
		abilityOn = true;
		normalSettings = camera->PostProcessSettings;

		NVsetting.bOverride_VignetteIntensity = true;
		NVsetting.bOverride_GrainJitter = true;
		NVsetting.bOverride_GrainIntensity = true;
		NVsetting.bOverride_WhiteTemp = true;
		NVsetting.bOverride_WhiteTint = true;
		NVsetting.bOverride_ColorSaturation = true;
		NVsetting.bOverride_ColorOffset = true;

		NVsetting.VignetteIntensity = 1.1;
		NVsetting.GrainJitter = 0.0;
		NVsetting.GrainIntensity = 0.476191;
		NVsetting.WhiteTemp = 6900;
		NVsetting.WhiteTint = -0.6;
		NVsetting.ColorSaturation = FVector4(1.0, 0.280875, 0.702882, 1.0);
		NVsetting.ColorOffset = FVector4(-0.185722, 0.0, -0.008505, 0.0);
		//NVsetting.bOverride_AutoExposureMinBrightness = true;
		//NVsetting.bOverride_AutoExposureMaxBrightness = true;
		//NVsetting.AutoExposureMinBrightness = 0.1f;
		//NVsetting.AutoExposureMaxBrightness = 0.1f;

		camera->PostProcessSettings = NVsetting;
	}
	else
		AbilityEnd();
}

void AABCatCharacter::AbilityEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("???"));
	abilityOn = false;
	//camera->PostProcessSettings.AutoExposureMaxBrightness = 1.0f;
	/*FPostProcessSettings NormalSetting;
	NormalSetting.bOverride_AutoExposureMinBrightness = true;
	NormalSetting.bOverride_AutoExposureMaxBrightness = true;
	NormalSetting.AutoExposureMinBrightness = 1.0f;
	NormalSetting.AutoExposureMaxBrightness = 8.0f;

	camera->PostProcessSettings = NormalSetting;*/
	camera->PostProcessSettings = normalSettings;
}