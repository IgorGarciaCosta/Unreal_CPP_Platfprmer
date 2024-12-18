// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "FallingInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API AFallingInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

	AFallingInteraction();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	//somilate falling behavior
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	//self referecne to facilitate respawning logic
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFallingInteraction>FallingInteractionClass;
	
	//delay to fall
	UPROPERTY(EditAnywhere)
	float DropDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float RespawnDelay = 2.f;

	//determine if the platform is destroyied after falling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bDestroy = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")

	bool bRespawn = true;

	FVector StartLocation;

	FTimerHandle TimerHandle;

	bool ALreadyOnFall;

public:
	UFUNCTION(BlueprintCallable)
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnFall();
	UFUNCTION(BlueprintCallable)
	void OnReset();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MakeTranslucid();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ResetOpacity();

};
