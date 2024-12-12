
// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeInteraction.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

ASpikeInteraction::ASpikeInteraction()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(PaperSprite);
}

void ASpikeInteraction::ChangeSpikeStats()
{
	bSpikeUp = !bSpikeUp;

	if (bSpikeUp) {
		BringSpikeDown();
	}
	else {
		BringSpikeUp();
	}
}

void ASpikeInteraction::BringSpikeUp()
{
	if (SpriteSpikeUp) {
		PaperSprite->SetSprite(SpriteSpikeUp);
		BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ASpikeInteraction::BringSpikeDown()
{
	if (SpriteSpikeDown) {
		PaperSprite->SetSprite(SpriteSpikeDown);
		BoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASpikeInteraction::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASpikeInteraction::BoxBeginOverlap);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpikeInteraction::ChangeSpikeStats, Duration, bLooping);
}

void ASpikeInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		if (!PlayerChar->bCanBeDamaged)return;
		PlayerChar->TakeDamage(DamageAmount, FDamageEvent(), nullptr, nullptr);
	}
}
