// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentActorInteraction.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"

// Sets default values
AParentActorInteraction::AParentActorInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = PaperSprite;
}

// Called when the game starts or when spawned
void AParentActorInteraction::BeginPlay()
{
	Super::BeginPlay();

	//using the player controller to get a player ref
	AController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController) {
		APawn* CurChar = PlayerController->GetPawn();
		PlayerChar = Cast< APlatformer2DCharacter>(CurChar);
	}
	
}

// Called every frame
void AParentActorInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

