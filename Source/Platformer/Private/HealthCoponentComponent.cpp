// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthCoponentComponent.h"
#include <DeathComponent.h>

// Sets default values for this component's properties
UHealthCoponentComponent::UHealthCoponentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthCoponentComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	
}


// Called every frame
void UHealthCoponentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthCoponentComponent::Revive()
{
	if (Owner == nullptr) return;
	Health = DefaultHealth;
	if (UDeathComponent* DeathComponent = Owner->FindComponentByClass<UDeathComponent>()) {
		DeathComponent->SetIsDead(false);
	}
}

void UHealthCoponentComponent::InitHealth()
{

	if (Owner == nullptr) return;

}

float UHealthCoponentComponent::TakeDamage(const float& Damage)
{
	UDeathComponent* DeathComponent = Owner->FindComponentByClass<UDeathComponent>();
	if (DeathComponent && Health > 0) {
		Health -= Damage;
		Health = FMath::Clamp(Health, 0, DefaultHealth);
		if (Health == 0 && !DeathComponent->IsDead()) {
			DeathComponent->OnDead();
		}
	}

	return Health;
}

