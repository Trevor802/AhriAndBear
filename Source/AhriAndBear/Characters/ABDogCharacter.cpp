// Fill out your copyright notice in the Description page of Project Settings.


#include "ABDogCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Environments/ABScentTrail.h"

AABDogCharacter::AABDogCharacter()
	: Super()
{

}

void AABDogCharacter::UseAbility()
{
	Super::UseAbility();

	//Xiubo, Add Scent Here ~ ~    xb: OK
	UE_LOG(LogTemp, Warning, TEXT("???"));
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AABScentTrail::StaticClass(), FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++)
	{
		AABScentTrail* scent = Cast<AABScentTrail>(FoundActors[i]);
		
		scent->ShowTrail();
	}
}
