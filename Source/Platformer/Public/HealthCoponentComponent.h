// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthCoponentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UHealthCoponentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthCoponentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float DefaultHealth;

	UPROPERTY(VisibleAnywhere)
	AActor* Owner;

public:
	UFUNCTION()
	FORCEINLINE float GetDefaultHealth() { return DefaultHealth; };
	FORCEINLINE void SetDefaultHealth(float newDefaultHealth) { DefaultHealth = newDefaultHealth; };

	FORCEINLINE float GetHealth() { return Health; };
	FORCEINLINE void UpdateHealth(float newHealth) { Health = newHealth; };

	UFUNCTION(BlueprintCallable)
	void Revive();

	UFUNCTION(BlueprintCallable)
	void InitHealth();

	UFUNCTION(BlueprintCallable)
	float TakeDamage(const float& Damage);

};
