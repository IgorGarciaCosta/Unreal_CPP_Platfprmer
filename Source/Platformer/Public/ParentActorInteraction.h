// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Platformer2DCharacter.h"
#include "GameFramework/Actor.h"
#include "ParentActorInteraction.generated.h"

UCLASS()
class PLATFORMER_API AParentActorInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentActorInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Interaction")
	class UPaperSpriteComponent* PaperSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")

	APlatformer2DCharacter* PlayerChar;

};
