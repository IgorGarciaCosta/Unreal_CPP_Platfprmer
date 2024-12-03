// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretInteraction.h"
#include "ProjectileCOmponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
ATurretInteraction::ATurretInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSprite"));
	RootComponent = PaperSprite;

	SceneComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SceneComp"));
	SceneComp->SetupAttachment(SceneComp);
}

// Called when the game starts or when spawned
void ATurretInteraction::BeginPlay()
{
	Super::BeginPlay();
	

	GetWorld()->GetTimerManager().SetTimer(TurretTimerHandle, this, &ATurretInteraction::Fire, DurationSpawn, bLooping);
}

// Called every frame
void ATurretInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretInteraction::Fire()
{
	if (ProjectileClass) {
		AProjectileCOmponent* ProjectileParent = GetWorld()->SpawnActor<AProjectileCOmponent>(
			ProjectileClass,
			SceneComp->GetComponentLocation(),
			SceneComp->GetComponentRotation()
		);
		if (ProjectileParent) {
			ProjectileParent->SetOwner(this);
		}

	}
}

