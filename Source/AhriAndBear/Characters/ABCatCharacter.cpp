// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCatCharacter.h"
#include "ABDogCharacter.h"
#include "ABPlayerController.h"

#include "Components/PawnNoiseEmitterComponent.h"
#include "Environments/ABScentSource.h"
#include "Perception/PawnSensingComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/Scene.h"

#include "Kismet/GameplayStatics.h"

static FVector ScentSourceLocationOffset = FVector(0, 0, 50);

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
	SetupNVParams();
	myScentSource =
		GetWorld()->SpawnActor<AABScentSource>(scentSourceBP, GetActorLocation() + ScentSourceLocationOffset, GetActorRotation());
	myScentSource->SetScentRange(1.f);
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
	if (!abilityOn)
	{
		camera->PostProcessSettings = nightVisionSettings;
	}
	else {
		camera->PostProcessSettings = normalSettings;
	}
	abilityOn = !abilityOn;
}

void AABCatCharacter::SetupNVParams()
{
	// Get the normal camera settings
	normalSettings = camera->PostProcessSettings;

	// Set up the camera settings
	nightVisionSettings.bOverride_VignetteIntensity = true;
	nightVisionSettings.bOverride_GrainJitter = true;
	nightVisionSettings.bOverride_GrainIntensity = true;
	nightVisionSettings.bOverride_WhiteTemp = true;
	nightVisionSettings.bOverride_WhiteTint = true;
	nightVisionSettings.bOverride_ColorSaturation = true;
	nightVisionSettings.bOverride_ColorOffset = true;
	nightVisionSettings.bOverride_ColorGamma = true;
	nightVisionSettings.VignetteIntensity = 1.1;
	nightVisionSettings.GrainJitter = 0.0;
	nightVisionSettings.GrainIntensity = 0.476191;
	nightVisionSettings.WhiteTemp = 6900;
	nightVisionSettings.WhiteTint = -0.6;
	nightVisionSettings.ColorSaturation = FVector4(1.0, 0.280875, 0.702882, 1.0);
	nightVisionSettings.ColorOffset = FVector4(-0.185722, 0.0, -0.008505, 0.0);
	nightVisionSettings.ColorGamma = nightVisionSettings.ColorGamma * 1.5;
}

void AABCatCharacter::UpdateCatScentSource()
{
	myScentSource->SetActorLocation(GetActorLocation() + ScentSourceLocationOffset);
}

EABAnimalMovementNoiseVolume AABCatCharacter::GetCurrentMovementVolume() const
{
	auto retVal = Super::GetCurrentMovementVolume();
	if (retVal != EABAnimalMovementNoiseVolume::Silent)
		retVal = EABAnimalMovementNoiseVolume::Quiet;
	return retVal;
}