#include "OccupyingInteractive.h"
#include "TimerManager.h"
#include "Interactives/CharacterInteractionComponent.h"

void AOccupyingInteractive::BeginInteraction()
{
    FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &AInteractive::AfterInteraction, true);
    GetWorldTimerManager().SetTimer(TimerHandle, timerDelegate, OccupyingDuration, false);
    InteractingComponent->SetOccupying(true);
    InteractingComponent->BeginInteraction(OccupyingDuration);
}

void AOccupyingInteractive::EndInteraction(bool bResult)
{
    check(InteractingComponent);
    InteractingComponent->SetOccupying(false);
    InteractingComponent->EndInteraction(bResult);
    GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AOccupyingInteractive::CallStopInteract()
{
    AfterInteraction(false);
}
