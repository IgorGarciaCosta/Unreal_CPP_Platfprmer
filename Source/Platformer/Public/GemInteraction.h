// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "GemInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API AGemInteraction : public AParentActorInteraction
{
	GENERATED_BODY()
	
public:
	AGemInteraction();


protected:
	virtual void BeginPlay();


	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	// Sound component to play sound when gem is collected
	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* GetItemSound;

	// Sound to be played
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* GetItemSoundBase;

	UFUNCTION(BlueprintCallable)
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
