// Fill out your copyright notice in the Description page of Project Settings.

#include "DistanceIndicator.h"
#include "ABAnimalCharacter.h"
#include "UI/DistanceIndicatorWidget.h"
// Called every frame
void UDistanceIndicator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	InjectData();
	UpdateTransform();
}

void UDistanceIndicator::BeginPlay()
{
	Super::BeginPlay();
	SetTintColorAndOpacity(TextColor);
	bInRange = false;
}

void UDistanceIndicator::UpdateTransform()
{
	auto widget = Cast<UDistanceIndicatorWidget>(GetUserWidgetObject());
	auto character = GET_CHARACTER;
	if (character == nullptr)
	{
		return;
	}
	FRotator PlayerRot = FRotationMatrix::MakeFromX(character->GetActorLocation() - GetComponentLocation()).Rotator();

	FVector WidgetLocation = GetComponentLocation();
	FVector TargetLocation = FVector(character->GetActorLocation().X, character->GetActorLocation().Y, WidgetLocation.Z);
	FVector Dir = (TargetLocation - WidgetLocation);
	Dir.Normalize();

	SetWorldRotation(Dir.Rotation());

	float dist = FVector::Dist(GetComponentLocation(), character->GetActorLocation()) / 100.f;
	widget->Distance = dist;
	if (dist <= 1)
	{
		SetVisibility(false);
	}
	else
	{
		SetVisibility(true);
	}
	widget->bInRange = bInRange;
	if (dist < RangeDistance && !bInRange)
	{
		widget->OnEnterRange();
		bInRange = true;
	}
	else if (dist >= RangeDistance && bInRange)
	{
		widget->OnExitRange();
		bInRange = false;
	}

}

void UDistanceIndicator::InjectData()
{
	auto widget = Cast<UDistanceIndicatorWidget>(GetUserWidgetObject());
	widget->ActorAttaching = GetOwner();
	widget->TextToDisplay = TextDisplay;
}
