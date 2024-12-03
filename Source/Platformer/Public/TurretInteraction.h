// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretInteraction.generated.h"

UCLASS()
class PLATFORMER_API ATurretInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TurretTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float DurationSpawn = 2;

	UPROPERTY(EditDefaultsOnly)
	bool bLooping = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Fire();

private:
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* PaperSprite;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectileCOmponent>ProjectileClass;

};
