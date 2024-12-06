// Fill out your copyright notice in the Description page of Project Settings.


#include "TrampolineInteraction.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>

ATrampolineInteraction::ATrampolineInteraction()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(PaperSprite);

	JumpSound = CreateDefaultSubobject<UAudioComponent>(TEXT("JumpSound"));
	JumpSound->SetupAttachment(RootComponent);
	JumpSound->bAutoActivate = false; // Do not play sound on start
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
		// Play the sound
		if (JumpSound && JumpSoundBase)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), JumpSoundBase, 1, 1, 0);
		}
	}
}

void ATrampolineInteraction::ResetTrampoline()
{

	if (TrampolineDownSprite) {
		PaperSprite->SetSprite(TrampolineDownSprite);
	}
}
