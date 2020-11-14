// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "Interactive.h"
#include "Misc/ScopeLock.h"
#include "FixedPulley.generated.h"

class UCableComponent;
UCLASS()
class AHRIANDBEAR_API AFixedPulley : public AInteractive
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    AFixedPulley();

protected:
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;
    void UpdateHandlers();
    class USceneComponent* Root;
    FORCEINLINE virtual bool CanInteract(UCharacterInteractionComponent*) const override { return true; }
    FORCEINLINE virtual void CallSprint() override {};
    FORCEINLINE virtual void CallStopSprint() override {};
    virtual void BeginInteraction() override;
    virtual void EndInteraction(bool) override;

public:	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
    class UCableComponent* ActionCable;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
    class UCableComponent* ReactionCable;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
    class USphereComponent* ActionHandler;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
    class USphereComponent* ReactionHandler;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    class AActor* ReactionObject;

private:
    void SwitchReaction(bool);

    float TotalLength = 200.0f;
    FVector ReleasedPoint;
    FCriticalSection Mutex;
};
