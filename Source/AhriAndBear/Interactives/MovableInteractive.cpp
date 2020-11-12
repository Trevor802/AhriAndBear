// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableInteractive.h"
#include "ABPlayerController.h"
#include "Components/InputComponent.h"
#include "ABPlayerController.h"
#include "CharacterInteractionComponent.h"

AMovableInteractive::AMovableInteractive()
{
    auto action = FInputActionBinding("Jump", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::Jump);
    ActionBindings.Add(action);
    action = FInputActionBinding("Sprint", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::Sprint);
    ActionBindings.Add(action);
    action = FInputActionBinding("Sprint", IE_Released);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::StopSprint);
    ActionBindings.Add(action);
    action = FInputActionBinding("Catch", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::Interact);
    ActionBindings.Add(action);
    action = FInputActionBinding("UseSkill", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::UseAbility);
    ActionBindings.Add(action);
    action = FInputActionBinding("AnimalTogether", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::Following);
    ActionBindings.Add(action);
    action = FInputActionBinding("ChangeAnimal", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::SwitchAnimal);
    ActionBindings.Add(action);
    action = FInputActionBinding("Crouch", IE_Pressed);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::Crouch);
    ActionBindings.Add(action);
    action = FInputActionBinding("Crouch", IE_Released);
    action.ActionDelegate.BindDelegate(this, &AMovableInteractive::StopCrouch);
    ActionBindings.Add(action);
    auto axis = FInputAxisBinding("WalkForward");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::MoveForward);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("WalkRight");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::MoveRight);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("TurnRate");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::TurnAtRate);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("LookUpRate");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::LookUpAtRate);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("Turn");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::Turn);
    AxisBindings.Add(axis);
    axis = FInputAxisBinding("LookUp");
    axis.AxisDelegate.BindDelegate(this, &AMovableInteractive::LookUp);
    AxisBindings.Add(axis);
}

void AMovableInteractive::CallMoveForward(float value)
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallMoveForward(value);
    }
}
void AMovableInteractive::CallMoveRight(float value)
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallMoveRight(value);
    }
}
void AMovableInteractive::CallTurn(float value)
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallTurn(value);
    }
}
void AMovableInteractive::CallLookUp(float value)
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallLookUp(value);
    }
}
void AMovableInteractive::CallTurnAtRate(float value)
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallTurnAtRate(value);
    }
}
void AMovableInteractive::CallLookUpAtRate(float value)
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallLookUpAtRate(value);
    }
}
void AMovableInteractive::CallJump()
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallJump();
    }
}
void AMovableInteractive::CallSprint()
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallSprint();
    }
}
void AMovableInteractive::CallStopSprint()
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallStopSprint();
    }
}
void AMovableInteractive::CallUseAbility()
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallUseAbility();
    }
}
void AMovableInteractive::CallFollowing()
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallFollowing();
    }
}
void AMovableInteractive::CallSwitchAnimal()
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallSwitchAnimal();
    }
}
void AMovableInteractive::CallCrouch()
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallCrouch();
    }
}
void AMovableInteractive::CallStopCrouch()
{
    if (InteractingComponent)
    {
        GET_CONTROLLER(InteractingComponent)->CallStopCrouch();
    }
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

void AMovableInteractive::CallInteract()
{
    if (InteractingComponent)
    {
        AfterInteraction(true);
    }
}

void AMovableInteractive::BindInput(UInputComponent* inputComponent) const
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

void AMovableInteractive::UnbindInput(UInputComponent* inputComponent) const
{
    for (auto& a : ActionBindings)
    {
        inputComponent->RemoveActionBindingForHandle(a.GetHandle());
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
