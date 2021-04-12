// Modified by Xiubo 2021/04/08
// Change pushing function to be manually triggered

#pragma once

#include "CoreMinimal.h"
#include "Interactives/Interactive.h"
#include "Characters/ABDogCharacter.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Interactives/CharacterInteractionComponent.h"

#include "PushingBox.generated.h"

#define RETURN_IF_NULL(x) if(!x) return;

enum InteractPosition {Left, Right, Front, Back, None};

class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
UCLASS()
class AHRIANDBEAR_API APushingBox : public AInteractive
{
	GENERATED_BODY()

public:
	APushingBox();
	APushingBox(const FObjectInitializer& OI);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual bool CanInteract(UCharacterInteractionComponent* interactingComponent) const override;
	FORCEINLINE virtual void CallSprint() override {};
	FORCEINLINE virtual void CallStopSprint() override {};

	class USceneComponent* Root;

	virtual void CallMoveForward(float) override;
	virtual void CallMoveRight(float value) override ;
	//virtual void CallTurn(float value)override {};
	virtual void BeginInteraction() override;
	virtual void EndInteraction(bool) override;

	void UpdateBox();
	bool CheckBoxMoveable();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Root")
		USceneComponent* sceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* boxMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Constraint")
		UPhysicsConstraintComponent* BoxJoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* trigger_left;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* trigger_right;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* trigger_front;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* trigger_back;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float pushingSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		bool NotInteractable = true;

private:
	UFUNCTION()
		void OnOverlapBegin_Left(
			class UPrimitiveComponent* OverlappedComp, 
			class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, 
			bool bFromSweep, 
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapBegin_Right(
			class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapBegin_Front(
			class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapBegin_Back(
			class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(
			class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	void LockMeshLocation();
	void EnterInteractPosition();

	bool horizontal;
	bool verticle;
	InteractPosition myInteractPosition = InteractPosition::None;
	FVector myPushDirection;
	bool bHeld;
	bool isInPosition = false; // if the character enters interaction position.
	float moveValue = 0.f;
	float enterPositionTimer = 0.f;
	float enterPositionDuration = 1.f;
	FRotator characterRotater;
	UBoxComponent* currentTrigger;
	FCollisionQueryParams myCollisionParams;
	FTransform characterTransform;
	FTransform interactTransform;
};