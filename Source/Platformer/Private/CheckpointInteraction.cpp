// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointInteraction.h"
#include <CharacterGameComponent.h>

ACheckpointInteraction::ACheckpointInteraction()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(PaperSprite);

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookomponent"));
	PaperFlipbookComponent->SetupAttachment(PaperSprite);

	Checkpoint = CreateDefaultSubobject<USceneComponent>(TEXT("Checkpoint"));
	Checkpoint->SetupAttachment(PaperSprite);
}

void ACheckpointInteraction::BeginPlay()
{
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointInteraction::BoxBeginOverlap);

}

void ACheckpointInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		if (UCharacterGameComponent* CharacterGameComponent = PlayerChar->FindComponentByClass<UCharacterGameComponent>()) {
			CharacterGameComponent->SetRespawnLocation(Checkpoint->GetComponentLocation());
		
			if (CheckpointOn) {
				PaperFlipbookComponent->SetFlipbook(CheckpointOn);
			}
		}
	
	}
}
