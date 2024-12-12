// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PlayerController.h"
#include "PaperFlipbookComponent.h"
#include "FinishingGameInteraction.generated.h"

/**
 * 
 */

UCLASS()
class PLATFORMER_API AFinishingGameInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

public:
	AFinishingGameInteraction();
	// Delegate to be broadcast when overlap begins
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedDelegate);
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnFinishedDelegate OnFinished;
protected:
	virtual void BeginPlay();


	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	// Sound component to play sound when gem is collected
	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* EnterAreaSound;

	// Sound to be played
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* EnterAreaSoundBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* PaperFlipbookComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbook* WavingFlag;

	UFUNCTION(BlueprintCallable)
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void FinishLevelEvents();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MoveFlagUp();

};
