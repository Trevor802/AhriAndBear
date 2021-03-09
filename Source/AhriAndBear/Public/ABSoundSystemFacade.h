// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/DialogueWave.h"
#include "ABSoundSystemFacade.generated.h"

class UUserSettings;

/**
 * Identifies the type of sound that should be played.
 */
UENUM(BlueprintType)
enum class EAccessibilitySoundType : uint8 {
	Music,
	SFX,
	Dialogue,
	Ambient,
};

/**
 * Provides sound methods that automatically mix the volumes properly.
 */
UCLASS()
class AHRIANDBEAR_API UABSoundSystemFacade : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Spawns a 2D sound using Ahri and Bear's accessibility settings.
	 * 
	 * @see UGameplayStatics::SpawnSound2D
	 * 
	 * @param soundType
	 *   The type of sound that this item is.
	 * @param sound
	 *	 The sound to spawn.
	 * @param volumeMultiplier
	 *   The volume to multiply the sound by. This will be multiplied by the settings for this sound type.
	 * @param pitchMultiplier
	 *   Multiplier by which to raise or lower the pitch.
	 * @param startTime
	 *   How far into the sound clip to start playing.
	 * @param soundConcurrency
	 *   The concurrency settings for this sound.
	 * @param persistAcrossLevelTransition
	 *   Should the sound exist across level transitions?
	 * @param autoDestroy
	 *   Should the returned sound component destroy itself?
	 *
	 * @return
	 *   The spawned sound.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sound")
	static UAudioComponent* ABSpawnSound2D(
		EAccessibilitySoundType soundType,
		USoundBase* sound,
		float volumeMultiplier = 1.f,
		float pitchMultiplier = 1.f,
		float startTime = 0.f,
		USoundConcurrency* soundConcurrency = nullptr,
		bool persistAcrossLevelTransition = false,
		bool autoDestroy = true
	);

	/**
	 * Spawns a sound at a location using Ahri and Bear's accessibility settings.
	 *
	 * @see UGameplayStatics::SpawnSoundAtLocation
	 *
	 * @param soundType
	 *   The type of sound that this item is.
	 * @param sound
	 *	 The sound to spawn.
	 * @param location
	 *   The location to spawn the sound at.
	 * @param rotation
	 *   The rotation to apply to the sound.
	 * @param volumeMultiplier
	 *   The volume to multiply the sound by. This will be multiplied by the settings for this sound type.
	 * @param pitchMultiplier
	 *   Multiplier by which to raise or lower the pitch.
	 * @param startTime
	 *   How far into the sound clip to start playing.
	 * @param soundConcurrency
	 *   The concurrency settings for this sound.
	 * @param persistAcrossLevelTransition
	 *   Should the sound exist across level transitions?
	 * @param autoDestroy
	 *   Should the returned sound component destroy itself?
	 *
	 * @return
	 *   The spawned sound.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sound")
	static UAudioComponent* ABSpawnSoundAtLocation(
		EAccessibilitySoundType soundType,
		USoundBase* sound,
		const FVector& location,
		const FRotator& rotation = FRotator::ZeroRotator,
		float volumeMultiplier = 1.f,
		float pitchMultiplier = 1.f,
		float startTime = 0.f,
		USoundAttenuation* attenuation = nullptr,
		USoundConcurrency* soundConcurrency = nullptr,
		bool bAutoDestroy = true
	);

	/**
	 * Spawns a sound at attached to an actor using Ahri and Bear's accessibility settings.
	 *
	 * @see UGameplayStatics::SpawnSoundAttached
	 *
	 * @param soundType
	 *   The type of sound that this item is.
	 * @param sound
	 *	 The sound to spawn.
	 * @param attachToComponent
	 *   The scene component to attach the sound to.
	 * @param AttachPointName
	 *   The name of the point to attach the sound to.
	 * @param location
	 *   The location to spawn the sound at.
	 * @param rotation
	 *   The rotation to apply to the sound.
	 * @param LocationType
	 *   The type of attach location.
	 * @param volumeMultiplier
	 *   The volume to multiply the sound by. This will be multiplied by the settings for this sound type.
	 * @param pitchMultiplier
	 *   Multiplier by which to raise or lower the pitch.
	 * @param startTime
	 *   How far into the sound clip to start playing.
	 * @param soundConcurrency
	 *   The concurrency settings for this sound.
	 * @param persistAcrossLevelTransition
	 *   Should the sound exist across level transitions?
	 * @param autoDestroy
	 *   Should the returned sound component destroy itself?
	 *
	 * @return
	 *   The spawned sound.
	 */
	UFUNCTION(BlueprintCallable, Category = "Sound")
	static UAudioComponent* ABSpawnSoundAttached(
		EAccessibilitySoundType soundType,
		USoundBase* sound,
		USceneComponent* attachToComponent,
		FName AttachPointName = NAME_None,
		FVector Location = FVector(ForceInit),
		FRotator Rotation = FRotator::ZeroRotator,
		EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset,
		bool bStopWhenAttachedToDestroyed = false,
		float volumeMultiplier = 1.f,
		float pitchMultiplier = 1.f,
		float startTime = 0.f,
		USoundAttenuation* AttenuationSettings = nullptr,
		USoundConcurrency* concurrencySettings = nullptr,
		bool bAutoDestroy = true
	);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	static void ABPlayDialogue2D(
		const UObject * WorldContextObject,
		UDialogueWave* Dialogue,
		const FDialogueContext& Context,
		float VolumeMultiplier = 1.f,
		float PitchMultiplier = 1.f,
		float StartTime = 0.f,
		EAccessibilitySoundType soundType = EAccessibilitySoundType::Dialogue
	);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	static void ABPlayDialogueAtLocation(
		const UObject* WorldContextObject,
		UDialogueWave* Dialogue,
		const FDialogueContext& Context,
		FVector Location,
		FRotator Rotation = FRotator::ZeroRotator,
		float volumeMultiplier = 1.f,
		float pitchMultiplier = 1.f,
		float startTime = 0.f,
		USoundAttenuation* attenuation = nullptr,
		EAccessibilitySoundType soundType = EAccessibilitySoundType::Dialogue
	);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	static void ABPlaySound2D(
		EAccessibilitySoundType soundType,
		const UObject* WorldContextObject,
		USoundBase* Sound,
		float volumeMultiplier = 1.f,
		float pitchMultiplier = 1.f,
		float startTime = 0.f,
		USoundConcurrency* ConcurrencySettings = nullptr,
		AActor* OwningActor = nullptr,
		bool bIsUISound = true
	);

	UFUNCTION(BlueprintCallable, Category = "Sound")
		static void ABPlaySoundAtLocation(
			EAccessibilitySoundType soundType,
			const UObject* WorldContextObject,
			USoundBase* Sound,
			FVector Location,
			FRotator Rotation = FRotator::ZeroRotator,
			float VolumeMultiplier = 1.f,
			float PitchMultiplier = 1.f,
			float StartTime = 1.f,
			USoundAttenuation* AttenuationSettings = nullptr,
			USoundConcurrency* ConcurrencySettings = nullptr,
			AActor* OwningActor = nullptr
		);

private:

	/**
	 * Retrieves user's settings.
	 * 
	 * @return
	 *   The user's settings.
	 */
	static UUserSettings* GetVolumeSettings();

	/**
	 * Gets the volume mixed by the sound type.
	 * 
	 * @param st:
	 *   The type of sound to get the volume for.
	 * @param inVolume:
	 *   The base volume for the sound being played.
	 * 
	 * @return
	 *   The final volume for the sound to be played.
	 */
	static float GetMixedVolumeBySoundType(EAccessibilitySoundType st, float inVolume);
};
