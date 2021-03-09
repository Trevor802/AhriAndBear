// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UserSettings.generated.h"

/**
 * Contains the player's user settings.
 */
UCLASS()
class AHRIANDBEAR_API UUserSettings : public USaveGame
{
	GENERATED_BODY()
public:

	/**
	* Where does this item get slaved?
	*/
	const FString SAVE_SLOT_NAME = TEXT("UserSettings");

	/**
	* What multiplier should we apply to volume in general?
	*/
	UPROPERTY(VisibleAnywhere, Category = Settings)
	float MasterVolume = 1.f;

	/**
	* What multiplier should we apply to the music?
	*/
	UPROPERTY(VisibleAnywhere, Category = Settings)
	float MusicVolume = 1.f;

	/**
	* What multiplier should we apply to the sound cues?
	*/
	UPROPERTY(VisibleAnywhere, Category = Settings)
	float SoundEffectVolume = 1.f;

	UPROPERTY(VisibleAnywhere, Category = Settings)
	float DialogueVolume = 1.f;

	/**
	* Should we show subtitles in the game? (WIP)
	*/
	UPROPERTY(VisibleAnywhere, Category = Settings)
	bool ShowSubtitles = false;

	/**
	* Constructs a user settings object.
	*/
	UUserSettings() { }

	/**
	* Retrieves the actual music volume.
	* 
	* @return MusicVolume * MasterVolume.
	*/
	UFUNCTION(BlueprintPure, Category = "Settings | Volume")
	FORCEINLINE float GetActualMusicVolume() const { return MusicVolume * MasterVolume; }

	/**
	* Retrieves the actual sound effect volume.
	* 
	* @return SoundEffectVolume * MasterVolume.
	*/
	UFUNCTION(BlueprintPure, Category = "Settings | Volume")
	FORCEINLINE float GetActualSoundEffectVolume() const { return SoundEffectVolume * MasterVolume; }
};
