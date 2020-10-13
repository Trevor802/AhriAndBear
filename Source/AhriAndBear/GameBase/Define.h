#pragma once
#include "CoreMinimal.h"
#include "Define.generated.h"

USTRUCT(BlueprintType)
struct FSurvivalData 
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Hunger;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Thirst;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Warmth;
};

USTRUCT(BlueprintType)
struct FAnimalData 
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FTransform		Transform;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FSurvivalData	SurvivalData;
};

UENUM(BlueprintType)
enum class EAnimalType : uint8
{
	Cat,
	Dog,
};
