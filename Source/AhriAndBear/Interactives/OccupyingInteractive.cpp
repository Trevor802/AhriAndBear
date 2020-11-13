#include "OccupyingInteractive.h"
#include "TimerManager.h"
#include "Interactives/CharacterInteractionComponent.h"

void AOccupyingInteractive::BeginInteraction()
{
    FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &AMovableInteractive::AfterInteraction, true);
    GetWorldTimerManager().SetTimer(TimerHandle, timerDelegate, OccupyingDuration, false);
    InteractingComponent->SetOccupying(true);
}

void AOccupyingInteractive::EndInteraction(bool)
{
    check(InteractingComponent);
    InteractingComponent->SetOccupying(false);
    GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AOccupyingInteractive::CallStopInteract()
{
    AfterInteraction(false);
}
