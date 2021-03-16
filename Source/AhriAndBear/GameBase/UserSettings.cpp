// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBase/UserSettings.h"
#include "Kismet/GameplayStatics.h"

void UUserSettings::SaveSettingsToDisc(const FAccessibilitySettings& settings) {
	UUserSettings* userSettings = Cast<UUserSettings>(UGameplayStatics::CreateSaveGameObject(UUserSettings::StaticClass()));
	if (userSettings) {
		userSettings->MasterVolume = settings.MasterVolume;
		userSettings->MusicVolume = settings.MusicVolume;
		userSettings->AmbientVolume = settings.AmbientVolume;
		userSettings->SoundEffectVolume = settings.SoundEffectVolume;
		userSettings->DialogueVolume = settings.DialogueVolume;
		userSettings->ShowSubtitles = settings.ShowSubtitles;
	}
	//UGameplayStatics::SaveGameToSlot(userSettings, GetSaveSlotName(), 0);
}

FAccessibilitySettings UUserSettings::LoadSettingsFromDisc() {
	auto game_save = UGameplayStatics::LoadGameFromSlot(GetSaveSlotName(), 0);
	UUserSettings* userSettings = Cast<UUserSettings>(game_save);

	return userSettings ? FAccessibilitySettings{
		userSettings->MasterVolume,
		userSettings->MusicVolume,
		userSettings->AmbientVolume,
		userSettings->SoundEffectVolume,
		userSettings->DialogueVolume,
		userSettings->ShowSubtitles,
	} : FAccessibilitySettings();
}
