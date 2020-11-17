// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPulley.h"
#include "Components/SphereComponent.h"
#include "Interactives/CharacterInteractionComponent.h"
#include "ABAnimalCharacter.h"
#include "ABPlayerController.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFixedPulley::AFixedPulley()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    ActionHandler = CreateDefaultSubobject<USphereComponent>(TEXT("ActionHandler"));
    ActionHandler->SetupAttachment(RootComponent);

    //UIWidget->SetupAttachment(ActionHandler);

    ReactionHandler = CreateDefaultSubobject<USphereComponent>(TEXT("ReactionHandler"));
    ReactionHandler->SetupAttachment(RootComponent);

    ActionCable = CreateDefaultSubobject<UCableComponent>(TEXT("ActionCable"));
    ActionCable->SetupAttachment(RootComponent);
    ReactionCable = CreateDefaultSubobject<UCableComponent>(TEXT("ReactionCable"));
    ReactionCable->SetupAttachment(RootComponent);
    ActionCable->EndLocation = FVector::ZeroVector;
    ReactionCable->EndLocation = FVector::ZeroVector;
    ActionCable->SetAttachEndToComponent(ActionHandler);
    ReactionCable->SetAttachEndToComponent(ReactionHandler);
    bOccupyMouth = true;
}

void AFixedPulley::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    ActionCable->SetAttachEndToComponent(ActionHandler);
    ReactionCable->SetAttachEndToComponent(ReactionHandler);
}

void AFixedPulley::BeginInteraction()
{
    SwitchReaction(true);
}

void AFixedPulley::EndInteraction(bool)
{
    SwitchReaction(false);
}

void AFixedPulley::SwitchReaction(bool isPulling)
{
    if (ReactionObject == nullptr)
        return;
    if (isPulling)
    {	
        ReactionHandler->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
        //UpdateHandlers();
        ReactionObject->AttachToComponent(ReactionHandler, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
        ReactionObject->SetActorLocation(ReactionHandler->GetComponentLocation());
        ReactionObject->SetActorRotation(FQuat::Identity);
        ReactionObject->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(false);
    }
    else
    {
        ReactionObject->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);
        ReactionHandler->AttachToComponent(ReactionObject->FindComponentByClass<UPrimitiveComponent>(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
        ReactionHandler->SetWorldLocation(ReactionObject->GetActorLocation());
        ActionHandler->SetWorldLocation(ReleasedPoint);
    }
}

// Called when the game starts or when spawned
void AFixedPulley::BeginPlay()
{
    Super::BeginPlay();
    ActionCable->SetAttachEndToComponent(ActionHandler);
    ReactionCable->SetAttachEndToComponent(ReactionHandler);
    ReleasedPoint = ActionHandler->GetComponentLocation();
    TotalLength = ActionHandler->GetRelativeLocation().Size() + (ReactionHandler->GetComponentLocation() - GetActorLocation()).Size();
}

// Called every frame
void AFixedPulley::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateHandlers();
}

void AFixedPulley::UpdateHandlers()
{
    if (InteractingComponent)
    {
        ActionHandler->SetWorldLocation(InteractingComponent->GetComponentLocation());
    }

    float startLength, endLength;
    if (InteractingComponent)
    {
        startLength = ActionHandler->GetRelativeLocation().Size();
        endLength = FMath::Clamp(TotalLength - startLength, 10.0f, TotalLength / 2);
        ReactionHandler->SetRelativeLocation(FVector(0, 0, -1) * endLength);
    }
}

void AFixedPulley::CallMoveForward(float value)
{
    RETURN_IF_NULL(InteractingComponent);
    auto v = GetActorLocation();
    auto controller = GET_CONTROLLER(InteractingComponent);
    RETURN_IF_NULL(controller);
    auto character = GET_CHARACTER(InteractingComponent);
    FVector actorBaseLoc = FVector(v.X, v.Y, character->GetActorLocation().Z);
    float distance = FVector::Distance(actorBaseLoc, character->GetActorLocation());
    FVector characterToBase = actorBaseLoc - character->GetActorLocation();
    FVector movingDir = FRotationMatrix(character->GetActorRotation()).GetUnitAxis(EAxis::X) * value;
    float dotProduct = FVector::DotProduct(characterToBase, movingDir);
    if (distance > TotalLength && dotProduct < 0 || !controller)
    {
        return;
    }
    else
    {
        controller->CallMoveForward(value);
    }
}

void AFixedPulley::CallMoveRight(float value)
{
    RETURN_IF_NULL(InteractingComponent);
    auto v = GetActorLocation();
    auto controller = GET_CONTROLLER(InteractingComponent);
    RETURN_IF_NULL(controller);
    auto character = GET_CHARACTER(InteractingComponent);
    FVector actorBaseLoc = FVector(v.X, v.Y, character->GetActorLocation().Z);
    float distance = FVector::Distance(actorBaseLoc, character->GetActorLocation());
    FVector characterToBase = actorBaseLoc - character->GetActorLocation();
    FVector movingDir = FRotationMatrix(character->GetActorRotation()).GetUnitAxis(EAxis::Y) * value;
    float dotProduct = FVector::DotProduct(characterToBase, movingDir);
    if (distance > TotalLength && dotProduct < 0 || !controller)
    {
        return;
    }
    else
    {
        controller->CallMoveRight(value);
    }
}
