
#include "ABScentSource.h"
#include "Components/SphereComponent.h"
#include "Characters/ABDogCharacter.h"
#include "Environments/ABScentIndicator.h"

// Sets default values
AABScentSource::AABScentSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	scentRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Scent Range"));
	scentRangeSphere->SetupAttachment(RootComponent);
	FScriptDelegate beginOverlapFunc;
	beginOverlapFunc.BindUFunction(this, TEXT("PlayerCharacterInRange"));
	FScriptDelegate endOverlapFunc;
	endOverlapFunc.BindUFunction(this, TEXT("PlayerCharacterOutRange"));

	scentRangeSphere->OnComponentBeginOverlap.Add(beginOverlapFunc);
	scentRangeSphere->OnComponentEndOverlap.Add(endOverlapFunc);
}

// Called when the game starts or when spawned
void AABScentSource::BeginPlay()
{
	Super::BeginPlay();
	dogInRange = nullptr;
	SetDogInRange(false);
}

bool AABScentSource::GetIsDogInRange()
{
	return isDogInRange;
}

void AABScentSource::SetDogInRange(bool isInRange)
{
	isDogInRange = isInRange;
}

void AABScentSource::PlayerCharacterInRange(AActor* self, AActor* OtherActor)
{
	dogInRange = Cast<AABDogCharacter>(OtherActor);
	if (dogInRange && !isDogInRange)
	{
		SetDogInRange(true);
	}
}

void AABScentSource::PlayerCharacterOutRange(AActor* self, AActor* OtherActor)
{
	dogInRange = Cast<AABDogCharacter>(OtherActor);
	if (dogInRange && isDogInRange)
	{
		SetDogInRange(false);
		dogInRange = nullptr;
	}
		
}

void AABScentSource::SpawnScentIndicator()
{
	if (!dogInRange)
		return;

	AABScentIndicator* indicator =
		GetWorld()->SpawnActor<AABScentIndicator>(dogInRange->GetActorLocation() + FVector(0, 30, 0), dogInRange->GetActorRotation());
	indicator->SetTargetPosition(GetActorLocation());
	indicator->SetIndicatorLifeSpan(5);
}

