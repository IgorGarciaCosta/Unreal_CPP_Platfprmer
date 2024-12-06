// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterGameComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStatWidget.h"
#include "Platformer2DCharacter.h"
#include "InputActionValue.h" // Ensure this is included
#include <HealthComponent.h>

// Sets default values
UCharacterGameComponent::UCharacterGameComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.
    PrimaryComponentTick.bCanEverTick = true;

    JumpSound = CreateDefaultSubobject<UAudioComponent>(TEXT("JumpSound"));
    JumpSound->bAutoActivate = false; // Do not play sound on start
}

// Called when the game starts or when spawned
void UCharacterGameComponent::BeginPlay()
{
    Super::BeginPlay();

    ComponentOwner = GetOwner();
    CurChar = Cast<APlatformer2DCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (ComponentOwner && CurChar) {
        RespawnLocation = ComponentOwner->GetActorLocation();
    }

    if (PlayerStatWidgetClass) {
        PlayerStatWidget = NewObject<UPlayerStatWidget>(this, PlayerStatWidgetClass);
        PlayerStatWidget->AddToViewport();
    }
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

void UCharacterGameComponent::MoveUpDown(const FInputActionValue& Value)
{
    if (CurChar && Value.GetMagnitude() != 0) {
        FVector WorldDir = FVector(0, 0, 1);
        CurChar->AddMovementInput(WorldDir, Value.GetMagnitude(), false);
    }
}

void UCharacterGameComponent::Jump()
{
    if (CurChar) {
        CurChar->Jump();
        SetJumping(true);
        // Play the sound
        if (JumpSound && JumpSoundBase)
        {
            UGameplayStatics::PlaySound2D(GetWorld(), JumpSoundBase, 1, 1, 0);
        }
    }
    
}

void UCharacterGameComponent::RespawnCharacter(FVector Location, bool bRelife)
{
    if (ComponentOwner) {
        ComponentOwner->SetActorLocation(Location);

        UDeathComponent* DeathComponent = ComponentOwner->FindComponentByClass<UDeathComponent>();
        if (DeathComponent) {
            DeathComponent->SetIsDead(true);
        }

        if (bRelife) {
            UHealthComponent* HealthComponent = ComponentOwner->FindComponentByClass<UHealthComponent>();
            HealthComponent->Revive();
        }
    }
}

float UCharacterGameComponent::IncrementGem()
{
    Gem += 1;
    return Gem;
}
