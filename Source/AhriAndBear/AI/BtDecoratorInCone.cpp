// Fill out your copyright notice in the Description page of Project Settings.


#include "BtDecoratorInCone.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/Character.h"

bool UBtDecoratorInCone::PerformConditionCheckAI(AAIController* ownerController, ACharacter* controlledPawn) {
	FVector actorLocation = controlledPawn->GetActorLocation();
	FVector forwardVector = controlledPawn->GetBaseAimRotation().Quaternion().GetForwardVector();

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector playerLocation = playerCharacter->GetActorLocation();

	FVector direction = playerLocation - actorLocation;

	float cosAngle = UKismetMathLibrary::Vector_CosineAngle2D(forwardVector, direction);
	float halfCosAngle = FMath::Cos(FMath::DegreesToRadians(HalfAngle));

	return halfCosAngle < cosAngle;
}