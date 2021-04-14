


#include "UI/HintTrigger.h"

// Sets default values
AHintTrigger::AHintTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHintTrigger::BeginOverlap);
}

void AHintTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Cast<AABAnimalCharacter>(OtherActor) && !bTriggered)
	{
		AABAnimalCharacter* tempChara = Cast<AABAnimalCharacter>(OtherActor);
		tempChara->HintString = TriggerHintString;
		tempChara->bShowHint = true;
		bTriggered = true;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("enter hint trigger"));
	}
}

// Called when the game starts or when spawned
void AHintTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHintTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

