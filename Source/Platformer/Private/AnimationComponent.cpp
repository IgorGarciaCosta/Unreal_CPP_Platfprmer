// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationComponent.h"
#include "Platformer2DCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h" // Include for UCharacterMovementComponent


// Sets default values for this component's properties
UAnimationComponent::UAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAnimationComponent::UpdateControlRotation()
{
	if (CurChar && CurChar->GetController()) {
		if (CurChar->GetCharacterMovement()->Velocity.X < 0.f) {//moving left
			FRotator Right = FRotator(0, 180, 0);
			CurChar->GetSprite()->SetRelativeRotation(Right);
			//CurChar->GetController()->SetControlRotation(Right);
		}

		else if (CurChar->GetCharacterMovement()->Velocity.X > 0.f) {//moving right
			FRotator Left = FRotator(0, 0, 0);
			CurChar->GetSprite()->SetRelativeRotation(Left);
			//CurChar->GetController()->SetControlRotation(Left);
		}

		else {//idle
			CharState = ECharacterState::Idle;
		}
	}
}


// Called when the game starts
void UAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	ComponentOwner = GetOwner();
	CurChar = Cast<APlatformer2DCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	
}


// Called every frame
void UAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateControlRotation();
}

