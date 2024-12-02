// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileCOmponent.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Platformer2DCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectileCOmponent::AProjectileCOmponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SceneComp);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(SceneComp);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

}

// Called when the game starts or when spawned
void AProjectileCOmponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerChar = Cast<APlatformer2DCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileCOmponent::SphereOverlapped);

}

// Called every frame
void AProjectileCOmponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileCOmponent::SphereOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerChar == nullptr) return;

	if (OtherActor == PlayerChar) {
		PlayerChar->TakeDamage(DamageAmount, FDamageEvent(), nullptr, nullptr);

		Destroy();
	}
}

