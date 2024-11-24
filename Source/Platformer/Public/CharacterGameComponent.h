// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h" // Ensure this is included for FInputActionValue
#include "CharacterGameComponent.generated.h"

UCLASS()
class PLATFORMER_API UCharacterGameComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    UCharacterGameComponent();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void MoveLeftRight(const FInputActionValue& Value);
    void Jump();

public:
    UPROPERTY(VisibleAnywhere)
    class APlatformer2DCharacter* CurChar;

    bool bJumping = false;

    UPROPERTY(VisibleAnywhere)
    AActor* ComponentOwner;

    FORCEINLINE bool GetJumping() const { return bJumping; }
    FORCEINLINE void SetJumping(bool bJumpingVal) { bJumping = bJumpingVal; }
};
