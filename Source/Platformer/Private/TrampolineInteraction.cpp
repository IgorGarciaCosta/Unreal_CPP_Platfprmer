// Fill out your copyright notice in the Description page of Project Settings.


#include "TrampolineInteraction.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

ATrampolineInteraction::ATrampolineInteraction()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(PaperSprite);
}

void ATrampolineInteraction::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ATrampolineInteraction::BoxBeginOverlap);

}

void ATrampolineInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		PlayerChar->LaunchCharacter(LaunchVelocity, false, true);

		if (TrampolineUpSprite) {
			PaperSprite->SetSprite(TrampolineUpSprite);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATrampolineInteraction::ResetTrampoline, Duration, false);

		}
	}
}

void ATrampolineInteraction::ResetTrampoline()
{

	if (TrampolineDownSprite) {
		PaperSprite->SetSprite(TrampolineDownSprite);
	}
}
