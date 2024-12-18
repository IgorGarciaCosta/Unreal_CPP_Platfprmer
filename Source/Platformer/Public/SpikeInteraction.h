// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "Platformer2DCharacter.h"
#include "SpikeInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API ASpikeInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

public:

	ASpikeInteraction();

	void ChangeSpikeStats();

	UFUNCTION(BlueprintCallable)
	void BringSpikeUp();
	UFUNCTION(BlueprintCallable)
	void BringSpikeDown();



protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool bSpikeUp = true;

	UPROPERTY(EditAnywhere)
	bool bLooping = true;

	UPROPERTY(EditAnywhere)
	float DamageAmount = 10;

	UPROPERTY(EditAnywhere)
	float Duration = 1;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	UFUNCTION(BlueprintCallable)
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	class UPaperSprite* SpriteSpikeUp;

	UPROPERTY(EditAnywhere)
	UPaperSprite* SpriteSpikeDown;

	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetLooping(bool loopVal) { bLooping = loopVal; };
	
};
