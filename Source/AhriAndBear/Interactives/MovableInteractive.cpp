// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableInteractive.h"
#include "ABPlayerController.h"
#include "CharacterInteractionComponent.h"

bool AMovableInteractive::TryInteracting(UCharacterInteractionComponent* component)
{
    if (bOccupyMouth && component->IsMouthInteracting()) return false;
    if (bOccupyPaw && component->IsPawInteracting()) return false;
    if (CanInteract(component))
    {
        InteractingComponent = component;
        if (bOccupyMouth)
            InteractingComponent->SetMouthInteracting(true);
        if (bOccupyPaw)
            InteractingComponent->SetPawInteracting(true);
        StopInteractionHandle = component->OnInteractionStopped.AddLambda([this]()
                                                                          {
                                                                              AfterInteraction(false);
                                                                          });
        return true;
    }
    return false;
}

void AMovableInteractive::BindInput(AABPlayerController* controller) const
{
    UInputComponent* playerInput = controller->InputComponent;
    //playerInput->actionbind
    //playerInput->BindAxis("WalkForward", this, &AABPlayerController::CallMoveForward);
    //playerInput->BindAxis("WalkRight", this, &AABPlayerController::CallMoveRight);
    //playerInput->BindAxis("TurnRate", this, &AABPlayerController::CallTurnAtRate);
    //playerInput->BindAxis("LookUpRate", this, &AABPlayerController::CallLookUpAtRate);
    //playerInput->BindAxis("Turn", this, &AABPlayerController::CallTurn);
    //playerInput->BindAxis("LookUp", this, &AABPlayerController::CallLookUp);

    //playerInput->BindAction("Catch", IE_Pressed, this, &AABPlayerController::CallInteract);
    //playerInput->BindAction("Jump", IE_Pressed, this, &AABPlayerController::CallJump);
    //playerInput->BindAction("Jump", IE_Released, this, &AABPlayerController::CallStopJump);
    //playerInput->BindAction("Jog", IE_Pressed, this, &AABPlayerController::CallSprint);
    //playerInput->BindAction("Jog", IE_Released, this, &AABPlayerController::CallStopSprint);
    //playerInput->BindAction("Crouch", IE_Pressed, this, &AABPlayerController::CallCrouch);
    //playerInput->BindAction("Crouch", IE_Released, this, &AABPlayerController::CallStopCrouch);
    //playerInput->BindAction("UseSkill", IE_Pressed, this, &AABPlayerController::CallUseAbility);
    //playerInput->BindAction("AnimalTogether", IE_Pressed, this, &AABPlayerController::CallFollowing);
    //playerInput->BindAction("ChangeAnimal", IE_Pressed, this, &AABPlayerController::CallSwitchAnimal);
    //playerInput->BindAction("ESC", IE_Pressed, this, &AABPlayerController::QuitGame);
}

void AMovableInteractive::UnbindInput(AABPlayerController*) const
{}

void AMovableInteractive::AfterInteraction(bool bResult)
{
    check(InteractingComponent);
    if (bOccupyMouth)
        InteractingComponent->SetMouthInteracting(false);
    if (bOccupyPaw)
        InteractingComponent->SetPawInteracting(false);
    InteractingComponent->OnInteractionStopped.Remove(StopInteractionHandle);
    InteractingComponent = nullptr;
}
