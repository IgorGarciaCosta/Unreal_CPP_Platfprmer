// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "Platformer2DCharacter.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "CheckpointInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API ACheckpointInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

public:
	ACheckpointInteraction();


protected:
	virtual void BeginPlay();

	int32 Counter = 0;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	UFUNCTION(BlueprintCallable)
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* PaperFlipbookComponent;
	

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Checkpoint;



	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* CheckpointOff;
	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* CheckpointOn;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayCheckpointSound();

};
