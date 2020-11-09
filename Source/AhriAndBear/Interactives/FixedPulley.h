// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "ABInteractiveObjectBase.h"
#include "Characters/ABCatCharacter.h"
#include "Characters/ABDogCharacter.h"
#include "Misc/ScopeLock.h"
#include "FixedPulley.generated.h"

class UCableComponent;
UCLASS()
class AHRIANDBEAR_API AFixedPulley : public AABInteractiveObjectBase
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    AFixedPulley();

protected:
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void AfterInteraction(bool) override;
    void UpdateHandlers();
    class USceneComponent* Root;

public:
    UFUNCTION()
        void OnStartOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
        void OnStartOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
        void OnEndOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
        void OnEndOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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
    AABDogCharacter* DogRef;
    AABCatCharacter* CatRef;

    bool bCanAttachDog;
    bool bCanAttachCat;

    bool bAttachingDog;
    bool bAttachingCat;
    float TotalLength = 200.0f;
    FVector ReleasedPoint;
    FCriticalSection Mutex;
};
