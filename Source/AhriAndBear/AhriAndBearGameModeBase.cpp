// Fill out your copyright notice in the Description page of Project Settings.


#include "AhriAndBearGameModeBase.h"

#include "Characters/ABDogCharacter.h"
#include "Characters/ABCatCharacter.h"

AAhriAndBearGameModeBase::AAhriAndBearGameModeBase()
{
	CurTaskIndex = 0;
}

void AAhriAndBearGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (LevelTasks.Num() != 0)
	{
		CurTaskText = LevelTasks[CurTaskIndex];
	}

	AActor* dogActor = UGameplayStatics::GetActorOfClass(GetWorld(), AABDogCharacter::StaticClass());
	dog = Cast<AABDogCharacter>(dogActor);
	if (dog != nullptr) {
		//dog->SurvivalComponent->OnCriticalConditionChanged.AddDynamic(this, &AAhriAndBearGameModeBase::OnAnimalCriticalConditionChanged);
		dog->OnAnimalCaught.AddDynamic(this, &AAhriAndBearGameModeBase::OnAnimalCaught);
	}

	AActor* catActor = UGameplayStatics::GetActorOfClass(GetWorld(), AABCatCharacter::StaticClass());
	cat = Cast<AABCatCharacter>(catActor);
	if (cat != nullptr) {
		//cat->SurvivalComponent->OnCriticalConditionChanged.AddDynamic(this, &AAhriAndBearGameModeBase::OnAnimalCriticalConditionChanged);
		cat->OnAnimalCaught.AddDynamic(this, &AAhriAndBearGameModeBase::OnAnimalCaught);
	}

	//AccessibilitySettings = UUserSettings::LoadSettingsFromDisc();
}

void AAhriAndBearGameModeBase::ToNextTask()
{
	if (CurTaskIndex < LevelTasks.Num())
	{
		CurTaskIndex++;
		CurTaskText = LevelTasks[CurTaskIndex];
	}
}

void AAhriAndBearGameModeBase::OnAnimalCriticalConditionChanged(UAABSurvivalComponent* sender, const FAnimalCriticalConditionChangedInfo& info)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, TEXT("An animal's critical condition changed! (Game Mode)"));
	// We've got to figure out what to do in this case.
	if (dog == nullptr || cat == nullptr) {
		return;
	}
	// We check both animals conditions. It's only game over if this is the case.
	if (dog->IsInCriticalCondition() && cat->IsInCriticalCondition()) {
#if UE_BUILD_DEVELOPMENT
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Game Over!"));
#endif
		EndGame(EGameOverReason::GO_AnimalsDead);
	}
}

void AAhriAndBearGameModeBase::OnAnimalCaught(AActor* captor) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Animal caught (game mode)"));
	EndGame(EGameOverReason::GO_AnimalCaught);
}

void AAhriAndBearGameModeBase::EndGame(EGameOverReason reason)
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	// If we need more information, the game mode can probably work it out.
	OnGameOver.Broadcast(FGameOverInfo(reason));
}
