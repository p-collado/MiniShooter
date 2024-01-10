// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHUD.generated.h"

class UTextBlock;
class UProgressBar;
class AShooterEnemy;

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UEnemyHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void SetCharacterOwner(AShooterEnemy* Char){ EnemyRef =  Char; }

	UFUNCTION()
	void ChangeLifeValue(const float NewValue);
	
	UPROPERTY(EditAnywhere)
	AShooterEnemy* EnemyRef;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* LifeBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LifeValue;
};
