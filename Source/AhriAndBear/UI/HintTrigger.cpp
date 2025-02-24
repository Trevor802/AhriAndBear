


#include "UI/HintTrigger.h"

// Sets default values
AHintTrigger::AHintTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHintTrigger::BeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AHintTrigger::OnTriggerOverlapEnd);
}

void AHintTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Cast<AABAnimalCharacter>(OtherActor) && !bTriggered)
	{
		bOverlappingCharacter = true;
		tempChara = Cast<AABAnimalCharacter>(OtherActor);
	}
}

void AHintTrigger::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && Cast<AABAnimalCharacter>(OtherActor))
	{
		bOverlappingCharacter = false;

		if (bCanReappear == true && tempChara && tempChara->bShowHint)
		{
			HideHint();
		}
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

	
	if (tempChara && bOverlappingCharacter && !bTriggered && !tempChara->bShowHint)
	{
		tempChara->HintString = TriggerHintString;
		tempChara->bShowHint = true;

		if (bCanReappear == false)
		{
			bTriggered = true;
			FTimerDelegate HintDelegate = FTimerDelegate::CreateUObject(this, &AHintTrigger::HideHint);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, HintDelegate, 5.0f, false);
		}
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("enter hint trigger"));
	}
}

void AHintTrigger::HideHint() 
{
	if (tempChara) 
	{
		tempChara->bShowHint = false;

		UABPlayerUIComponent* UIComponent = tempChara->FindComponentByClass<UABPlayerUIComponent>();
		UIComponent->HideHintUI();
	}
}

