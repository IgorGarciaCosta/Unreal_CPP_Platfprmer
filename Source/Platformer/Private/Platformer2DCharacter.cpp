// Fill out your copyright notice in the Description page of Project Settings.


#include "Platformer2DCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CharacterGameComponent.h"
#include "PlayerStatWidget.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"

APlatformer2DCharacter::APlatformer2DCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComp->SetupAttachment(RootComponent);

	CharacterGameComponent = CreateDefaultSubobject<UCharacterGameComponent>(TEXT("CharacterGameComponent"));

	AnimComp = CreateDefaultSubobject<UAnimationComponent>(TEXT("AnimComp"));

	DeathComp = CreateDefaultSubobject<UDeathComponent>(TEXT("DeathComp"));
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));


}

void APlatformer2DCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlatformer2DCharacter::Jump()
{
	Super::Jump();
	if (CharacterGameComponent) {
		CharacterGameComponent->SetJumping(true);
	}
}

void APlatformer2DCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (CharacterGameComponent) {
		CharacterGameComponent->SetJumping(false);
	}

}

void APlatformer2DCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (MovementAction) {
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlatformer2DCharacter::EnhancedMove);
		}

		if (ClimbAction) {
			PlayerEnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Triggered, this, &APlatformer2DCharacter::EnhancedClimb);
		}

		if (JumpAction) {
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlatformer2DCharacter::EnhancedJump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlatformer2DCharacter::EnhancedJump);

		}
	}
}

float APlatformer2DCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (HealthComponent) {
		float UpdatedHealth = HealthComponent->TakeDamage(ActualDamage);
	
		if (UpdatedHealth == 0) {
			CharacterGameComponent->RespawnCharacter(CharacterGameComponent->GetRespawnLocation(), true);
			UpdatedHealth = HealthComponent->GetHealth();
		}

		float MaxHealth = HealthComponent->GetDefaultHealth();
		if (CharacterGameComponent) {
			CharacterGameComponent->GetPlayerStatWidget()->UpdateHealthBar(UpdatedHealth, MaxHealth);
		}
	}

	

	return ActualDamage;
}

//informs unreal we are adopting enhanced input
void APlatformer2DCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	//retrieve local player
	if (APlayerController* LocalPlayer = Cast<APlayerController>(GetController())) {
		//get input local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer->GetLocalPlayer())) {
			//clear existing mappings
			Subsystem->ClearAllMappings();

			//add new mapping context
			Subsystem->AddMappingContext(InputMappingContext, InputPriority);
		}
	}
}

void APlatformer2DCharacter::EnhancedMove(const FInputActionValue& Value)
{
	if (CharacterGameComponent) {
		CharacterGameComponent->MoveLeftRight(Value);
	}
}

void APlatformer2DCharacter::EnhancedClimb(const FInputActionValue& Value)
{
	if (CharacterGameComponent) {
		CharacterGameComponent->MoveUpDown(Value);
	}
}

void APlatformer2DCharacter::EnhancedJump(const FInputActionValue& Value)
{
	if (CharacterGameComponent) {
		CharacterGameComponent->Jump();
	}
}
