// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStatWidget.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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
		if (DynamicMat) {
			const float Percent = Health / MaxHealth;
			//PlayerHealthBar->SetPercent(Percent);
			DynamicMat->SetScalarParameterValue(FName("Progress"), Percent);
		}
		//PlayerHealthBar->SetPercent(Percent);
	}
}

void UPlayerStatWidget::UpdateGem(float Gem)
{
	NumberOfGems->SetText(FText::AsNumber(Gem));
}
