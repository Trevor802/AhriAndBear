// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableInteractive.h"
#include "ABPlayerController.h"
#include "Components/InputComponent.h"
#include "ABPlayerController.h"
#include "CharacterInteractionComponent.h"

AMovableInteractive::AMovableInteractive()
{
    auto action = FInputActionBinding("Jump", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallJump);
    ActionBindings.Add(&action);
    action = FInputActionBinding("Sprint", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallSprint);
    ActionBindings.Add(&action);
    action = FInputActionBinding("Sprint", IE_Released);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallStopSprint);
    ActionBindings.Add(&action);
    action = FInputActionBinding("Catch", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallInteract);
    ActionBindings.Add(&action);
    action = FInputActionBinding("Catch", IE_Released);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallStopInteract);
    ActionBindings.Add(&action);
    action = FInputActionBinding("UseSkill", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallUseAbility);
    ActionBindings.Add(&action);
    action = FInputActionBinding("AnimalTogether", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallFollowing);
    ActionBindings.Add(&action);
    action = FInputActionBinding("ChangeAnimal", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallSwitchAnimal);
    ActionBindings.Add(&action);
    action = FInputActionBinding("Crouch", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallCrouch);
    ActionBindings.Add(&action);
    action = FInputActionBinding("Crouch", IE_Released);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::CallStopCrouch);
    ActionBindings.Add(&action);
    auto axis = FInputAxisBinding("WalkForward");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::CallMoveForward);
    AxisBindings.Add(&axis);
    axis = FInputAxisBinding("WalkRight");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::CallMoveRight);
    AxisBindings.Add(&axis);
    axis = FInputAxisBinding("TurnRate");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::CallTurnAtRate);
    AxisBindings.Add(&axis);
    axis = FInputAxisBinding("LookUpRate");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::CallLookUpAtRate);
    AxisBindings.Add(&axis);
    axis = FInputAxisBinding("Turn");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::CallTurn);
    AxisBindings.Add(&axis);
    axis = FInputAxisBinding("LookUp");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::CallLookUp);
    AxisBindings.Add(&axis);
}

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
        Controller = Cast<AABPlayerController>(Cast<APawn>(InteractingComponent->GetOwner())->GetController());
        Controller->UnbindInput();
        BindInput(Controller->InputComponent);
        return true;
    }
    return false;
}

void AMovableInteractive::BindInput(UInputComponent* inputComponent) const
{
    for (auto& a : ActionBindings)
    {
        inputComponent->AddActionBinding(*a);
    }
    for (auto& a : AxisBindings)
    {
        inputComponent->AxisBindings.Add(*a);
    }
}

void AMovableInteractive::UnbindInput(UInputComponent* inputComponent) const
{
    for (auto& a : ActionBindings)
    {
        inputComponent->RemoveActionBindingForHandle(a->GetHandle());
    }
    for (auto& a : AxisBindings)
    {
        //inputComponent->AxisBindings.RemoveSwap(*a);
        inputComponent->AxisBindings.RemoveAllSwap([&a](const FInputAxisBinding& x)
                                                   {
                                                       return x.AxisName == a->AxisName;
                                                   });
    }
}

void AMovableInteractive::AfterInteraction(bool bResult)
{
    check(InteractingComponent);
    if (bOccupyMouth)
        InteractingComponent->SetMouthInteracting(false);
    if (bOccupyPaw)
        InteractingComponent->SetPawInteracting(false);
    UnbindInput(Controller->InputComponent);
    Controller->BindInput();
    InteractingComponent = nullptr;
}
