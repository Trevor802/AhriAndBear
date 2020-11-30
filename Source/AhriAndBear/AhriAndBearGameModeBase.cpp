// Fill out your copyright notice in the Description page of Project Settings.


#include "AhriAndBearGameModeBase.h"

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
}

void AAhriAndBearGameModeBase::ToNextTask()
{
	if (CurTaskIndex < LevelTasks.Num())
	{
		CurTaskIndex++;
		CurTaskText = LevelTasks[CurTaskIndex];
	}
}
