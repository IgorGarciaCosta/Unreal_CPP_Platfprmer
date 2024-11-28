// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "TrampolineInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API ATrampolineInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

	ATrampolineInteraction();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LaunchVelocity = FVector(0, 0, 600);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* TrampolineUpSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* TrampolineDownSprite;


	UFUNCTION(BlueprintCallable)
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle TimerHandle;

	void ResetTrampoline();
};
