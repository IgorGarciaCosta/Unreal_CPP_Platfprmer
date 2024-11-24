// Fill out your copyright notice in the Description page of Project Settings.


#include "Platformer2DCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlatformer2DCharacter::APlatformer2DCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComp->SetupAttachment(RootComponent);
}

void APlatformer2DCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlatformer2DCharacter::EnhancedMove(const FInputActionValue& Value)
{
}

void APlatformer2DCharacter::EnhancedJump(const FInputActionValue& Value)
{
}
