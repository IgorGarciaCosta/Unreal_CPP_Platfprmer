// Fill out your copyright notice in the Description page of Project Settings.


#include "LadderInteraction.h"
#include "Components/BoxComponent.h"
#include "Platformer2DCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <CharacterGameComponent.h>

// Sets default values
ALadderInteraction::ALadderInteraction()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALadderInteraction::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ALadderInteraction::BoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ALadderInteraction::BoxEndOverlap);

	//using the player controller to get a player ref
	AController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController) {
		APawn* CurChar = PlayerController->GetPawn();
		PlayerChar = Cast< APlatformer2DCharacter>(CurChar);
	}
}

// Called every frame
void ALadderInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadderInteraction::BoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		PlayerChar->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

		if (UCharacterGameComponent* CharacterGameComponent = PlayerChar->FindComponentByClass<UCharacterGameComponent>()) {
			CharacterGameComponent->SetOnLadder(true);
		}
	}


}

void ALadderInteraction::BoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		PlayerChar->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		if (UCharacterGameComponent* CharacterGameComponent = PlayerChar->FindComponentByClass<UCharacterGameComponent>()) {
			CharacterGameComponent->SetOnLadder(false);
		}
	}
}

