// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySimple.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

AEnemySimple::AEnemySimple()
{
}

void AEnemySimple::BeginPlay()
{
	Super::BeginPlay();

	bMoveRight = FMath::RandBool();

	AEnemyBase::ToggleFacingDirection();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemySimple::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemySimple::OnSphereOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AEnemySimple::OnSphereEndOverlap);

}

void AEnemySimple::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	if (!bAlreadyHit) {
		bAlreadyHit = true;
		AEnemySimple::OnCapsuleComponentHit(OtherActor, Hit.Normal);
	}
}

void AEnemySimple::OnCapsuleComponentHit(AActor* OtherActor, FVector HitNormal)
{
	Super::OnCapsuleComponentHit(OtherActor, HitNormal);

	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) {
		if (HitNormal.X != 0) {
			bMoveRight = !bMoveRight;
			AEnemyBase::ToggleFacingDirection();
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemySimple::ResetHit, .2, false);

		}
	}
}

void AEnemySimple::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap( OverlappedComponent, OtherActor, OtherComp,  OtherBodyIndex,  bFromSweep,  SweepResult);
	if (bCanFollowChar && OtherActor == PlayerChar) {
		bFollowingChar = true;
		Move();
	}
}

void AEnemySimple::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (bCanFollowChar && OtherActor == PlayerChar) {
		bFollowingChar = false;
	}
}

void AEnemySimple::ResetHit()
{
	bAlreadyHit = false;
}

void AEnemySimple::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Move();

	if (bCanFollowChar && bFollowingChar)
	{
		FollowCharacter();
	}
}
