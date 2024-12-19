// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "DeathComponent.h"
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

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;
	

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneComp;

	bool bCanBeDamaged = true;
	FORCEINLINE void ReenableDamage() {bCanBeDamaged = true;
	};
	FTimerHandle DamageTimerHandle;

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

	UPROPERTY(VisibleAnywhere)
	class UCharacterGameComponent* CharacterGameComponent;

	UPROPERTY(VisibleAnywhere)
	UAnimationComponent* AnimComp;
	
	UPROPERTY(VisibleAnywhere)
	UDeathComponent* DeathComp;

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent;


	UFUNCTION(BlueprintImplementableEvent)
	void MoveToFinishGame();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayDamageSound();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExecuteDamageEffects();
};
