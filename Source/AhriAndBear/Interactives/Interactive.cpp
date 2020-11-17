// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive.h"
#include "ABPlayerController.h"
#include "Components/InputComponent.h"
#include "ABPlayerController.h"
#include "CharacterInteractionComponent.h"

AInteractive::AInteractive()
{
    auto action = FInputActionBinding("Jump", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AInteractive::Jump);
    ActionBindings.Add(action);
    action = FInputActionBinding("Sprint", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AInteractive::Sprint);
    ActionBindings.Add(action);
    action = FInputActionBinding("Sprint", IE_Released);
    action.ActionDelegate.BindDelegate(this, &AInteractive::StopSprint);
    ActionBindings.Add(action);
    action = FInputActionBinding("Catch", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AInteractive::Interact);
    ActionBindings.Add(action);
    action = FInputActionBinding("Catch", IE_Released);
    action.ActionDelegate.BindDelegate(this, &AInteractive::StopInteract);
    ActionBindings.Add(action);
    action = FInputActionBinding("UseSkill", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AInteractive::UseAbility);
    ActionBindings.Add(action);
    action = FInputActionBinding("AnimalTogether", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AInteractive::Following);
    ActionBindings.Add(action);
    action = FInputActionBinding("Crouch", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AInteractive::Crouch);
    ActionBindings.Add(action);
    action = FInputActionBinding("Crouch", IE_Released);
    action.ActionDelegate.BindDelegate(this, &AInteractive::StopCrouch);
    ActionBindings.Add(action);
    auto axis = FInputAxisBinding("WalkForward");
    axis.AxisDelegate.BindDelegate(this, &AInteractive::MoveForward);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("WalkRight");
    axis.AxisDelegate.BindDelegate(this, &AInteractive::MoveRight);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("TurnRate");
    axis.AxisDelegate.BindDelegate(this, &AInteractive::TurnAtRate);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("LookUpRate");
    axis.AxisDelegate.BindDelegate(this, &AInteractive::LookUpAtRate);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("Turn");
    axis.AxisDelegate.BindDelegate(this, &AInteractive::Turn);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("LookUp");
    axis.AxisDelegate.BindDelegate(this, &AInteractive::LookUp);
    AxisBindings.Add(axis);
}

void AInteractive::CallMoveForward(float value)
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallMoveForward(value);
        }
    }
}
void AInteractive::CallMoveRight(float value)
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallMoveRight(value);
        }
    }
}
void AInteractive::CallTurn(float value)
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallTurn(value);
        }
    }
}
void AInteractive::CallLookUp(float value)
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallLookUp(value);
        }
    }
}
void AInteractive::CallTurnAtRate(float value)
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallTurnAtRate(value);
        }
    }
}
void AInteractive::CallLookUpAtRate(float value)
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallLookUpAtRate(value);
        }
    }
}
void AInteractive::CallJump()
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallJump();
        }
    }
}
void AInteractive::CallSprint()
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallSprint();
        }
    }
}
void AInteractive::CallStopSprint()
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallStopSprint();
        }
    }
}
void AInteractive::CallUseAbility()
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallUseAbility();
        }
    }
}
void AInteractive::CallFollowing()
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallFollowing();
        }
    }
}
void AInteractive::CallCrouch()
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if (controller)
        {
            controller->CallCrouch();
        }
    }
}
void AInteractive::CallStopCrouch()
{
    if (InteractingComponent)
    {
        auto controller = GET_CONTROLLER(InteractingComponent);
        if(controller)
        {
            controller->CallStopCrouch();
        }
    }
}

bool AInteractive::TryInteracting(UCharacterInteractionComponent* component)
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
        BeginInteraction();
        Controller = Cast<AABPlayerController>(Cast<APawn>(InteractingComponent->GetOwner())->GetController());
        Controller->UnbindInput();
        BindInput(Controller->InputComponent);
        return true;
    }
    return false;
}

void AInteractive::CallInteract()
{
    if (InteractingComponent)
    {
        AfterInteraction(true);
    }
}

void AInteractive::BindInput(UInputComponent* inputComponent) const
{
    for (auto& a : ActionBindings)
    {
        inputComponent->AddActionBinding(a);
    }
    for (auto& a : AxisBindings)
    {
        inputComponent->AxisBindings.Add(a);
    }
}

void AInteractive::UnbindInput(UInputComponent* inputComponent) const
{
    for (auto& a : ActionBindings)
    {
        inputComponent->RemoveActionBinding(a.GetActionName(), a.KeyEvent);
    }
    for (auto& a : AxisBindings)
    {
        //inputComponent->AxisBindings.RemoveSwap(*a);
        inputComponent->AxisBindings.RemoveAllSwap([&a](const FInputAxisBinding& x)
                                                   {
                                                       return x.AxisName == a.AxisName;
                                                   });
    }
}

void AInteractive::AfterInteraction(bool bResult)
{
    check(InteractingComponent);
    EndInteraction(bResult);
    if (bOccupyMouth)
        InteractingComponent->SetMouthInteracting(false);
    if (bOccupyPaw)
        InteractingComponent->SetPawInteracting(false);
    UnbindInput(Controller->InputComponent);
    Controller->BindInput();
    InteractingComponent->ClearInteractingActor();
    InteractingComponent = nullptr;
}
