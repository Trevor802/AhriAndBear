// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AccessibilitySettings.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, Category = "Settings | Accessibility")
struct AHRIANDBEAR_API FAccessibilitySettings
{
	GENERATED_BODY()
public:

	/**
	* What multiplier should we apply to volume in general?
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings | Accessibility | Sound")
		float MasterVolume = 1.f;

	/**
	* What multiplier should we apply to the music?
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings | Accessibility | Sound")
		float MusicVolume = 1.f;

	/**
	* What multiplier should we apply to the ambient sounds?
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings | Accessibility | Sound")
		float AmbientVolume = 1.f;

	/**
	* What multiplier should we apply to the sound cues?
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings | Accessibility | Sound")
		float SoundEffectVolume = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings | Accessibility | Sound")
		float DialogueVolume = 1.f;

	/**
	* Should we show subtitles in the game? (WIP)
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings | Accessibility | Sound")
		bool ShowSubtitles = false;
		
};
