// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterGameComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Platformer2DCharacter.h"
#include "InputActionValue.h" // Ensure this is included

// Sets default values
UCharacterGameComponent::UCharacterGameComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UCharacterGameComponent::BeginPlay()
{
    Super::BeginPlay();

    ComponentOwner = GetOwner();
    CurChar = Cast<APlatformer2DCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void UCharacterGameComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Add any ticking behavior here
}

void UCharacterGameComponent::MoveLeftRight(const FInputActionValue& Value)
{
    if (CurChar && Value.GetMagnitude() != 0) {
        FVector WorldDir = FVector(1, 0, 0);
        CurChar->AddMovementInput(WorldDir, Value.GetMagnitude(), false);
    }
}

void UCharacterGameComponent::Jump()
{
    if (CurChar) {
        CurChar->Jump();
        SetJumping(true);
    }
    
}
