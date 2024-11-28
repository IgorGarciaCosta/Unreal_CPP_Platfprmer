// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperFlipbook.h"
#include "AnimationComponent.generated.h"


UENUM(BlueprintType)
enum ECharacterState {
	Idle, 
	Run, 
	Jump, 
	Attack, 
	Fall,
	Dead
};

USTRUCT(BlueprintType)
struct FAnimationStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "structs")
	TEnumAsByte<ECharacterState> AnimationState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "structs")
	UPaperFlipbook* AnimationFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "structs")
	bool bIsLoopingAnimation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimationComponent();

	void UpdateControlRotation();

	void AnimationStateMachine();
	bool RunAnimation();
	bool JumpAnimation();
	bool AttackAnimation();
	bool DeathAnimation();

	void UpdateAnimation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, Category="Character")
	class APlatformer2DCharacter* CurChar;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	AActor* ComponentOwner;

	TEnumAsByte<ECharacterState> CharState = ECharacterState::Idle;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "flipbooks")
	TArray<FAnimationStruct> AnimationStructs;

	FAnimationStruct CurAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "flipbooks")
	UPaperFlipbook* AttackFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "flipbooks")
	UPaperFlipbook* RunFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "flipbooks")
	UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "flipbooks")
	UPaperFlipbook* JumpFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "flipbooks")
	UPaperFlipbook* FallFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "flipbooks")
	UPaperFlipbook* DeathFlipbook;

};
