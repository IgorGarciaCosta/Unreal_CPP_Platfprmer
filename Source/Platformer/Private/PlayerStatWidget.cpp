// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStatWidget.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "Components/ProgressBar.h"
#include <HealthComponent.h>

void UPlayerStatWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPlayerStatWidget::InitHealthWidget, .3, false);

}

void UPlayerStatWidget::InitHealthWidget()
{
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (PlayerChar) {
		if (UHealthComponent* HealthComp = PlayerChar->FindComponentByClass<UHealthComponent>()) {
			const float Health = HealthComp->GetHealth();
			const float MaxHealth = HealthComp->GetDefaultHealth();
		
			UpdateHealthBar(Health, MaxHealth);
		}
	}

}

void UPlayerStatWidget::UpdateHealthBar(float Health, float MaxHealth)
{
	if (Health >= 0 && MaxHealth > 0) {
		const float Percent = Health / MaxHealth;
		PlayerHealthBar->SetPercent(Percent);
	}
}
