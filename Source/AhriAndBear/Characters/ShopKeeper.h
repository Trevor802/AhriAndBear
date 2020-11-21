// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShopKeeper.generated.h"

UCLASS()
class AHRIANDBEAR_API AShopKeeper : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(Category = "Shopkeeper", VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(Category = "Shopkeeper", VisibleDefaultsOnly)
		class UBoxComponent* Box1;

	UPROPERTY(Category = "Shopkeeper", VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(Category = "Positions", EditAnywhere)
		TArray<AActor*> PatrolPositions;

public:
	// Sets default values for this character's properties
	AShopKeeper();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	TArray<AActor*> GetPatrolPositions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBox1BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
