// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishingGameInteraction.h"
#include <CharacterGameComponent.h>
#include "PlayerStatWidget.h"
#include <Kismet/GameplayStatics.h>

AFinishingGameInteraction::AFinishingGameInteraction()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);

	EnterAreaSound = CreateDefaultSubobject<UAudioComponent>(TEXT("EnterAreaSound"));
	EnterAreaSound->SetupAttachment(RootComponent);
	EnterAreaSound->bAutoActivate = false; // Do not play sound on start

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(RootComponent);
}

void AFinishingGameInteraction::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFinishingGameInteraction::BoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AFinishingGameInteraction::BoxEndOverlap);

	PaperFlipbookComponent->Stop();
}

void AFinishingGameInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		
		// Broadcast the delegate
		OnFinished.Broadcast();
		FinishLevelEvents();
		// Play the sound
		if (EnterAreaSound && EnterAreaSoundBase)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), EnterAreaSoundBase, 1, 1, 0);
		}
		PlayerChar->CharacterGameComponent->GetPlayerStatWidget()->RunFinishEvents();
		
	}
}

void AFinishingGameInteraction::BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AFinishingGameInteraction::FinishLevelEvents()
{
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerChar->DisableInput(PlayerController);
		PlayerChar->AnimComp->bIsGameOver = true;
		PlayerChar->AnimComp->SetCharState(ECharacterState::Run);
		PlayerChar->AnimComp->UpdateAnimation();
		PlayerChar->MoveToFinishGame();
	}
	PaperFlipbookComponent->Play();
	MoveFlagUp();
}
