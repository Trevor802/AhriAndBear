
#include "ABScentIndicator.h"
#include "Components/SphereComponent.h"

// Sets default values
AABScentIndicator::AABScentIndicator()
{
	sensor = CreateDefaultSubobject<USphereComponent>(TEXT("Unit Sensor"));
	sensor->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AABScentIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABScentIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

