// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingInteraction.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFallingInteraction::AFallingInteraction()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(PaperSprite);
	

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->SetActive(false);
}

void AFallingInteraction::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFallingInteraction::BoxBeginOverlap);
}

void AFallingInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFallingInteraction::OnFall, DropDelay, false);

	}
}

void AFallingInteraction::OnFall()
{
	if (ProjectileMovementComponent) {
		ProjectileMovementComponent->ProjectileGravityScale = 1;
		ProjectileMovementComponent->SetActive(true);

		if (PaperSprite) {
			PaperSprite->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFallingInteraction::OnReset, RespawnDelay, false);
	}
}

void AFallingInteraction::OnReset()
{
	if (FallingInteractionClass == nullptr) return;

	if (bDestroy) {
		Destroy();
	}

	if (bRespawn) {
		GetWorld()->SpawnActor<AFallingInteraction>(FallingInteractionClass, StartLocation, GetActorRotation());
	}
}
