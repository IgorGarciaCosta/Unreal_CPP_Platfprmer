// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "AnimationComponent.h"
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

	virtual void Jump() override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;
	

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneComp;

	virtual void PawnClientRestart() override;

#pragma region INPUT

protected:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ClimbAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	int32 InputMappingPriority = 0;


public:
	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedClimb(const FInputActionValue& Value);
	void EnhancedJump(const FInputActionValue& Value);
#pragma endregion INPUT

private:
	UPROPERTY(VisibleAnywhere)
	class UCharacterGameComponent* CharacterGameComponent;

	UPROPERTY(VisibleAnywhere)
	UAnimationComponent* AnimComp;
};
