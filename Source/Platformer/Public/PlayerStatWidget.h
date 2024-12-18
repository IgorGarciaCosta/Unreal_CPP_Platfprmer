// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void InitHealthWidget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(BindWidget))
	class UProgressBar* PlayerHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NumberOfGems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMat;

	UFUNCTION(BlueprintCallable) 
	void UpdateHealthBar(float Health, float MaxHealth); 

	UFUNCTION(BlueprintCallable)
	void UpdateGem(float Gem);

private:
	FTimerHandle TimerHandle;
	
};
