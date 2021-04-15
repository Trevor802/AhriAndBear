


#include "UI/EndTrigger.h"

// Sets default values
AEndTrigger::AEndTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AEndTrigger::BeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AEndTrigger::OnTriggerOverlapEnd);
}

void AEndTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Cast<AABAnimalCharacter>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("overlapping end trigger"));
		bOverlappingCharacter = true;
		tempChara = Cast<AABAnimalCharacter>(OtherActor);
	}
}

void AEndTrigger::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && Cast<AABAnimalCharacter>(OtherActor))
	{
		bOverlappingCharacter = false;
	}
}

// Called when the game starts or when spawned
void AEndTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (tempChara && bOverlappingCharacter && !tempChara->bShowEndWidget)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("overlapping end trigger"));
		if (Doors.Num() == 1)
		{
			if (Doors[0]->bOpened) 
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("show end widget"));
				tempChara->bShowEndWidget = true;
			}
		}
	}
}

