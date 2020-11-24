#include "OccupyingInteractive.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Interactives/CharacterInteractionComponent.h"

void AOccupyingInteractive::BeginInteraction()
{
    FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &AInteractive::AfterInteraction, true);
    GetWorldTimerManager().SetTimer(TimerHandle, timerDelegate, OccupyingDuration, false);
    InteractingComponent->SetOccupying(true);
    InteractingComponent->BeginInteraction(OccupyingDuration);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractingSound, GetActorLocation());
}

void AOccupyingInteractive::EndInteraction(bool bResult)
{
    check(InteractingComponent);
    InteractingComponent->SetOccupying(false);
    InteractingComponent->EndInteraction(bResult);
    GetWorldTimerManager().ClearTimer(TimerHandle);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), bResult ? SuccessSound : FailSound, GetActorLocation());
}

void AOccupyingInteractive::CallStopInteract()
{
    AfterInteraction(false);
}
