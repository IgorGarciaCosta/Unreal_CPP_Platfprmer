// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemySimple.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API AEnemySimple : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemySimple();

private:
	UPROPERTY(EditAnywhere)
	bool bAlreadyHit = false;
	UPROPERTY(EditAnywhere)
	bool bCanFollowChar = false;

	virtual void BeginPlay()override;

	UFUNCTION(BlueprintCallable)
	virtual void OnHit(
		UPrimitiveComponent* HitComponent,    // The component that was hit
		AActor* OtherActor,                   // The other actor involved in the collision
		UPrimitiveComponent* OtherComp,       // The other component involved in the collision
		FVector NormalImpulse,                // The impulse applied to the HitComponent due to the collision
		const FHitResult& Hit                 // Detailed information about the hit
	);

	UFUNCTION(BlueprintCallable)
	virtual void OnCapsuleComponentHit(AActor* OtherActor,FVector HitNormal);

	UFUNCTION(BlueprintCallable)
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION(BlueprintCallable)
	virtual void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	void ResetHit();

	FTimerHandle TimerHandle;

public:

	virtual void Tick(float DeltaSeconds)override;

};
