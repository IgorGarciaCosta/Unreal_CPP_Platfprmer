// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Platformer2DCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API APlatformer2DCharacter : public APaperCharacter
{
	GENERATED_BODY()

	APlatformer2DCharacter();

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComp;
};
