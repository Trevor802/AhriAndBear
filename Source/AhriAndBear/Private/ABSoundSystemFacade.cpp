// Fill out your copyright notice in the Description page of Project Settings.


#include "ABSoundSystemFacade.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "../GameBase/UserSettings.h"
#include "../AhriAndBearGameModeBase.h"

UAudioComponent* UABSoundSystemFacade::ABSpawnSound2D(
	EAccessibilitySoundType soundType,
	USoundBase* sound,
	float volumeMultiplier,
	float pitchMultiplier,
	float startTime,
	USoundConcurrency* soundConcurrency,
	bool persistAcrossLevelTransition,
	bool autoDestroy
)
{
	float actualVolume = volumeMultiplier * GetMixedVolumeBySoundType(soundType, volumeMultiplier);

	UAudioComponent* spawnedSound = UGameplayStatics::SpawnSound2D(
		GEngine->GetWorld(),
		sound,
		actualVolume,
		pitchMultiplier,
		startTime,
		soundConcurrency,
		persistAcrossLevelTransition,
		autoDestroy
	);

	return spawnedSound;
}

UAudioComponent* UABSoundSystemFacade::ABSpawnSoundAtLocation(EAccessibilitySoundType soundType, USoundBase* sound, const FVector& location, const FRotator& rotation, float volumeMultiplier, float pitchMultiplier, float startTime, USoundAttenuation* attenuation, USoundConcurrency* soundConcurrency, bool bAutoDestroy)
{
	float actualVolume = GetMixedVolumeBySoundType(soundType, volumeMultiplier);
	return UGameplayStatics::SpawnSoundAtLocation(
		GEngine->GetWorld(),
		sound,
		location,
		rotation,
		actualVolume,
		pitchMultiplier,
		startTime,
		attenuation,
		soundConcurrency,
		bAutoDestroy
	);
}

UAudioComponent* UABSoundSystemFacade::ABSpawnSoundAttached(EAccessibilitySoundType soundType, USoundBase* sound, USceneComponent* attachToComponent, FName AttachPointName, FVector Location, FRotator Rotation, EAttachLocation::Type LocationType, bool bStopWhenAttachedToDestroyed, float volumeMultiplier, float pitchMultiplier, float startTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* concurrencySettings, bool bAutoDestroy)
{
	float actualVolume = GetMixedVolumeBySoundType(soundType, volumeMultiplier);
	return UGameplayStatics::SpawnSoundAttached(
		sound,
		attachToComponent,
		AttachPointName,
		Location,
		Rotation,
		LocationType,
		bStopWhenAttachedToDestroyed,
		actualVolume,
		pitchMultiplier,
		startTime,
		AttenuationSettings,
		concurrencySettings,
		bAutoDestroy
	);
}

void UABSoundSystemFacade::ABPlayDialogue2D(const UObject* WorldContextObject, UDialogueWave* Dialogue, const FDialogueContext& Context, float volumeMultiplier, float PitchMultiplier, float StartTime, EAccessibilitySoundType soundType)
{
	float actualVolume = GetMixedVolumeBySoundType(soundType, volumeMultiplier);
	UGameplayStatics::PlayDialogue2D(
		WorldContextObject,
		Dialogue,
		Context,
		actualVolume,
		PitchMultiplier,
		StartTime
	);
}

void UABSoundSystemFacade::ABPlayDialogueAtLocation(const UObject* WorldContextObject, UDialogueWave* Dialogue, const FDialogueContext& Context, FVector Location, FRotator Rotation, float volumeMultiplier, float pitchMultiplier, float startTime, USoundAttenuation* attenuation, EAccessibilitySoundType soundType)
{
	float actualVolume = GetMixedVolumeBySoundType(soundType, volumeMultiplier);
	UGameplayStatics::PlayDialogueAtLocation(
		WorldContextObject,
		Dialogue,
		Context,
		Location,
		Rotation,
		actualVolume,
		pitchMultiplier,
		startTime,
		attenuation
	);
}

void UABSoundSystemFacade::ABPlaySound2D(EAccessibilitySoundType soundType, const UObject* WorldContextObj, USoundBase* Sound, float volumeMultiplier, float pitchMultiplier, float startTime, USoundConcurrency* Concurrency, AActor* OwningActor, bool bIsUISound)
{
	float actualVolume = GetMixedVolumeBySoundType(soundType, volumeMultiplier);
	UGameplayStatics::PlaySound2D(
		WorldContextObj,
		Sound,
		actualVolume,
		pitchMultiplier,
		startTime,
		Concurrency,
		OwningActor,
		bIsUISound
	);
}

void UABSoundSystemFacade::ABPlaySoundAtLocation(EAccessibilitySoundType soundType, const UObject* WorldContextObject, USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, AActor* OwningActor)
{
	float actualVolume = GetMixedVolumeBySoundType(soundType, VolumeMultiplier);
	UGameplayStatics::PlaySoundAtLocation(
		WorldContextObject,
		Sound,
		Location,
		Rotation,
		actualVolume,
		PitchMultiplier,
		StartTime,
		AttenuationSettings,
		ConcurrencySettings,
		OwningActor
	);
}

// vvvvvvvvvvvvvvvvvvvvvv
// Private static methods
// ^^^^^^^^^^^^^^^^^^^^^^
UUserSettings* UABSoundSystemFacade::GetVolumeSettings()
{
	AActor* gameModeActor = UGameplayStatics::GetActorOfClass(GEngine->GetWorld(), AAhriAndBearGameModeBase::StaticClass());
	if (!gameModeActor) {
		return nullptr;
	}
	AAhriAndBearGameModeBase* gameMode = Cast<AAhriAndBearGameModeBase>(gameModeActor);
	if (!gameMode) return nullptr;

	return gameMode->userSettings;
}

float UABSoundSystemFacade::GetMixedVolumeBySoundType(EAccessibilitySoundType st, float inVolume)
{
	auto userSettings = GetVolumeSettings();
	if (!userSettings) {
		// Let's make sure to report an error here
		return 1.f;
	}
	float masterVolume = userSettings->MasterVolume * inVolume;

	switch (st) {
	case EAccessibilitySoundType::Music:
		return userSettings->MusicVolume * masterVolume;
	case EAccessibilitySoundType::SFX:
		return userSettings->SoundEffectVolume * masterVolume;
	case EAccessibilitySoundType::Dialogue:
		return userSettings->DialogueVolume * masterVolume;
	case EAccessibilitySoundType::Ambient:
		return userSettings->AmbientVolume * masterVolume;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown sound category %s"), st);
		return 1.f;
	}
}
