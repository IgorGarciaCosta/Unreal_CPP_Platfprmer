// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationComponent.h"
#include "Platformer2DCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h" // Include for UCharacterMovementComponent
#include <CharacterGameComponent.h>


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

void UAnimationComponent::AnimationStateMachine()
{
	DeathAnimation();
	AttackAnimation();
	FallAnimation();
	ClimbAnimation();
	JumpAnimation();
	RunAnimation();
}

bool UAnimationComponent::RunAnimation()
{
	if (CurChar && !ClimbAnimation() &&!JumpAnimation() && !FallAnimation()) {
		float Velocity = CurChar->GetCharacterMovement()->Velocity.Length();
		bool bFalling = CurChar->GetCharacterMovement()->IsFalling();

		if (Velocity > 0 && !bFalling && !AttackAnimation()) {
			CharState = ECharacterState::Run;
			return true;
		}
		if (Velocity == 0) {
			CharState = ECharacterState::Idle;
		}
	
	}
	return false;
}

bool UAnimationComponent::JumpAnimation()
{
	if (CurChar &&!ClimbAnimation()) {
		if (UCharacterGameComponent* CharacterGameComponent = ComponentOwner->FindComponentByClass<UCharacterGameComponent>()) {
			if (CharacterGameComponent->GetJumping()) {
				CharState = ECharacterState::Jump;
				return true;
			}
		}
	}

	return false;
}

bool UAnimationComponent::FallAnimation()
{
	if (CurChar) {
		if (UCharacterGameComponent* CharacterGameComponent = ComponentOwner->FindComponentByClass<UCharacterGameComponent>()) {
			if (CurChar->GetCharacterMovement()->IsFalling()) {
				CharState = ECharacterState::Fall;
				return true;
			}
		}
	}

	return false;
}

bool UAnimationComponent::ClimbAnimation()
{
	if (CurChar) {
		if (UCharacterGameComponent* CharacterGameComponent = ComponentOwner->FindComponentByClass<UCharacterGameComponent>()) {
			if (CharacterGameComponent->GetOnLadder()) {
				const float Velocity = CurChar->GetCharacterMovement()->Velocity.Length();
				if (Velocity > 0) {
					CharState = ECharacterState::Climb;
				}
				else {
					CharState = ECharacterState::IdleClimb;

				}
				return true;
			}
			
		}
		
	}
	return false;
}

bool UAnimationComponent::AttackAnimation()
{
	return false;
}

bool UAnimationComponent::DeathAnimation()
{
	return false;
}

void UAnimationComponent::UpdateAnimation()
{
	if (CurChar == nullptr) return;

	if (!AnimationStructs.IsEmpty()) {
		for (FAnimationStruct AnimElement : AnimationStructs) {
			if (AnimElement.AnimationFlipbook && AnimElement.AnimationState == CharState) {
				CurAnim = AnimElement;
				CurChar->GetSprite()->SetFlipbook(AnimElement.AnimationFlipbook);
				CurChar->GetSprite()->SetLooping(AnimElement.bIsLoopingAnimation);
				
				if(CurAnim.bIsLoopingAnimation){
					CurChar->GetSprite()->Play();
				}
				break;
			}
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

	if (bIsGameOver)return;
	UpdateControlRotation();
	AnimationStateMachine();
	UpdateAnimation();
}

