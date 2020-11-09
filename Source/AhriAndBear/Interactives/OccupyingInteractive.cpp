#include "OccupyingInteractive.h"
#include "TimerManager.h"
#include "Interactives/CharacterInteractionComponent.h"

bool AOccupyingInteractive::TryInteracting(UCharacterInteractionComponent* component)
{
    if (component->IsOccupying())
    {
        return false;
    }
    if (CanInteract(component))
    {
        InteractingComponent = component;
        FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &AOccupyingInteractive::AfterInteraction, true);
        GetWorldTimerManager().SetTimer(TimerHandle, timerDelegate, OccupyingDuration, false);
        InteractingComponent->SetOccupying(true);
        StopInteractionHandle = component->OnInteractionStopped.AddLambda([this]()
                                                  {
                                                      AfterInteraction(false);
                                                  });
        return true;
    }
    return false;
}

void AOccupyingInteractive::AfterInteraction(bool bResult)
{
    check(InteractingComponent);
    InteractingComponent->SetOccupying(false);
    InteractingComponent->OnInteractionStopped.Remove(StopInteractionHandle);
    GetWorldTimerManager().ClearTimer(TimerHandle);
    InteractingComponent = nullptr;
}
