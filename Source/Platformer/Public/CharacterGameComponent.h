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
    void MoveUpDown(const FInputActionValue& Value);
    void Jump();
    void RespawnCharacter(FVector Location, bool bRelife);

public:
    UPROPERTY(VisibleAnywhere)
    class APlatformer2DCharacter* CurChar;

    bool bJumping = false;

    bool bOnLadder = false;

    FVector RespawnLocation;

    UPROPERTY(VisibleAnywhere)
    AActor* ComponentOwner;

    FORCEINLINE bool GetJumping() const { return bJumping; }
    FORCEINLINE void SetJumping(bool bJumpingVal) { bJumping = bJumpingVal; }
    FORCEINLINE bool GetOnLadder() const { return bOnLadder; }
    FORCEINLINE void SetOnLadder(bool bLadderVal) { bOnLadder = bLadderVal; }

    FORCEINLINE FVector GetRespawnLocation() const { return RespawnLocation; }
    FORCEINLINE void SetRespawnLocation(FVector RespawnLocationVal) { RespawnLocation = RespawnLocationVal; }

};
