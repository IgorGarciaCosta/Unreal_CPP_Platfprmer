// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include <Kismet/GameplayStatics.h>
#include "Components/CapsuleComponent.h"


AEnemyBase::AEnemyBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize and set up the sphere component
    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComp->InitSphereRadius(100.0f);
    SphereComp->SetupAttachment(GetSprite());

    // Initialize and set up the health component
    HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

    // Initialize and set up the death component
    DeathComponent = CreateDefaultSubobject<UDeathComponent>(TEXT("DeathComponent"));
}

void AEnemyBase::BeginPlay()
{
    Super::BeginPlay();
    // Additional initialization logic can go here
    PlayerChar = Cast<APlatformer2DCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void AEnemyBase::BeginDestroy()
{
    Super::BeginDestroy();
    // Cleanup logic can go here
}

void AEnemyBase::ToggleFacingDirection()
{
    if (GetSprite()) {
        const FVector WorldScale = GetSprite()->K2_GetComponentScale();
        float DirectionValue = 1;

        if (!bMoveRight) {
            DirectionValue = -1;
        }

        const float NewScaleX = FMath::Abs(WorldScale.X) * DirectionValue;
        const FVector NewScale = FVector(NewScaleX, WorldScale.Y, WorldScale.Z);
        GetSprite()->SetWorldScale3D(NewScale);
    }
}

void AEnemyBase::Move()
{
    if (!bFollowingChar) {
        float FacingDirec = 1;
        if (bMoveRight) {
            FacingDirec = -1;
        }
        AddMovementInput(EWorldDirection, FacingDirec);
    }
}

void AEnemyBase::FollowCharacter()
{
    if (PlayerChar == nullptr) return;
    const FVector EWorldLocation = GetCapsuleComponent()->K2_GetComponentLocation();
    const FVector PWorldlLocation = PlayerChar->GetCapsuleComponent()->K2_GetComponentLocation();

    const float DiffScale = PWorldlLocation.X - EWorldLocation.X;

    if (DiffScale >= 0 && bFollowingChar) {
        if (bFollowingChar) {
            bMoveRight = false;
        }
    }
    else {

        if (bFollowingChar) {
            bMoveRight = true;
        }
    }

    ToggleFacingDirection();

    if (FMath::Abs(DiffScale) > MaxDistanceBetweenChar) {
        AddMovementInput(EWorldLocation, DiffScale);
    }

}

void AEnemyBase::OnHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    // Handle hit logic here
}

void AEnemyBase::OnSphereOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    // Handle overlap logic here
}

void AEnemyBase::OnSphereEndOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex
)
{
    // Handle end overlap logic here
}