// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameInstance.h"

void UABGameInstance::Clear() 
{
	AnimalSurvivalData.Empty();
}

bool UABGameInstance::Has(const EAnimalType animalType) const 
{ 
	return AnimalSurvivalData.Contains(animalType); 
}

void UABGameInstance::Add(const EAnimalType animalType, const FAnimalData& survivalData) 
{ 
	AnimalSurvivalData.Add(animalType, survivalData); 
}

FAnimalData UABGameInstance::Get(const EAnimalType animalType) const
{ 
	return AnimalSurvivalData[animalType]; 
}
