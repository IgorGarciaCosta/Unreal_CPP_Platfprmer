// Fill out your copyright notice in the Description page of Project Settings.


#include "GemInteraction.h"
#include "PlayerStatWidget.h"
#include <CharacterGameComponent.h>

AGemInteraction::AGemInteraction()
{

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);

}

void AGemInteraction::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AGemInteraction::BoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AGemInteraction::BoxEndOverlap);

}

void AGemInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		UCharacterGameComponent* CharacterGameComponent = PlayerChar->FindComponentByClass<UCharacterGameComponent>();
		const float CurrentGem = CharacterGameComponent->IncrementGem();
		CharacterGameComponent->GetPlayerStatWidget()->UpdateGem(CurrentGem);
		Destroy();
	}
}

void AGemInteraction::BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {

	}
}
