// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include <Components/SphereComponent.h>
#include <HealthComponent.h>
#include <DeathComponent.h>
#include <Platformer2DCharacter.h>
#include "EnemyBase.generated.h"


/**
 *
 */
UCLASS()
class PLATFORMER_API AEnemyBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:

	virtual void BeginPlay()override;
	virtual void BeginDestroy()override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere)
	UDeathComponent* DeathComponent;

	UPROPERTY(EditAnywhere)
	APlatformer2DCharacter* PlayerChar;

public:
	void ToggleFacingDirection();


#pragma region MOVEMENT
	void Move();

	void FollowCharacter();
#pragma endregion MOVEMENT

	virtual void OnCapsuleComponentHit(AActor* OtherActor, FVector Normal) {};
	virtual void OnHit(
		UPrimitiveComponent* HitComponent,    // The component that was hit
		AActor* OtherActor,                   // The other actor involved in the collision
		UPrimitiveComponent* OtherComp,       // The other component involved in the collision
		FVector NormalImpulse,                // The impulse applied to the HitComponent due to the collision
		const FHitResult& Hit                 // Detailed information about the hit
	);

	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent, // The component that is being overlapped
		AActor* OtherActor,                       // The other actor involved in the overlap
		UPrimitiveComponent* OtherComp,           // The other component involved in the overlap
		int32 OtherBodyIndex,                     // The index of the other body in the collision
		bool bFromSweep,                          // Whether the overlap is from a sweep
		const FHitResult& SweepResult             // Hit result if the overlap was from a sweep
	);

	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent, // The component that is ending the overlap
		AActor* OtherActor,                       // The other actor involved in ending the overlap
		UPrimitiveComponent* OtherComp,           // The other component involved in ending the overlap
		int32 OtherBodyIndex                      // The index of the other body in the collision
	);

protected:
	UPROPERTY(EditAnywhere)
	bool bMoveRight = false;

	UPROPERTY(EditAnywhere)
	bool bFollowingChar = false;

	UPROPERTY(EditAnywhere)
	FVector EWorldDirection = FVector(1, 0, 0);

	UPROPERTY(EditAnywhere)
	float MaxDistanceBetweenChar = 40;
};
