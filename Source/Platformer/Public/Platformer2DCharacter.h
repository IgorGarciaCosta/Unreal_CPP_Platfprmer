// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Platformer2DCharacter.generated.h"


class UInputAction;
class UInputMappingContext;
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

#pragma region INPUT

protected:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	int32 InputMappingPriority = 0;


public:
	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedJump(const FInputActionValue& Value);
#pragma endregion INPUT
};
