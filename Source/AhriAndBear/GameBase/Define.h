#pragma once
#include "CoreMinimal.h"
#include "Containers/Union.h"
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

UENUM(BlueprintType)
enum class EEventType : uint8
{
	SaveGame,
	LoadLevel,
	GainWarmth,
	Supply,
};

UENUM(BlueprintType)
enum class ELevelName : uint8
{
	Default	 = 0,
	Level2_1 = 1,
	Level2_2 = 2,
	Level2_3 = 3,
};

USTRUCT(BlueprintType)
struct FEventData
{
	GENERATED_BODY()

	//FEventData() {};
	//FEventData(FEventData&&) {};
	//FEventData(const FEventData&) = default;
	//FEventData& operator=(const FEventData&) = default;
	//~FEventData() {};
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEventType TriggerEvent;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//TUnion<uint8, float> Data;
	union
	{
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		//uint8 LevelID;
		ELevelName LevelID;
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float GainWarmthRate;
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FSurvivalData SurvivalData;
	};
};
