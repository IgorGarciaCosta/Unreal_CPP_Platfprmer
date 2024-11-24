// Fill out your copyright notice in the Description page of Project Settings.


#include "Platformer2DCharacter.h"
#include "GameFramework/SpringArmComponent.h"

#include "CharacterGameComponent.h"
#include "Camera/CameraComponent.h"

APlatformer2DCharacter::APlatformer2DCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComp->SetupAttachment(RootComponent);

	CharacterGameComponent = CreateDefaultSubobject<UCharacterGameComponent>(TEXT("CharacterGameComponent"));
}

void APlatformer2DCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlatformer2DCharacter::Jump()
{
	Super::Jump();
	if (CharacterGameComponent) {
		CharacterGameComponent->SetJumping(true);
	}
}

void APlatformer2DCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (CharacterGameComponent) {
		CharacterGameComponent->SetJumping(false);
	}

}

void APlatformer2DCharacter::EnhancedMove(const FInputActionValue& Value)
{
	if (CharacterGameComponent) {
		CharacterGameComponent->MoveLeftRight(Value);
	}
}

void APlatformer2DCharacter::EnhancedJump(const FInputActionValue& Value)
{
	if (CharacterGameComponent) {
		CharacterGameComponent->Jump();
	}
}
