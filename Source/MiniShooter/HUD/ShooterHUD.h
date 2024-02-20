// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterHUD.generated.h"

class ACharacterBase;
class UTextBlock;
class UProgressBar;
class AMiniShooterHud;
/**
 * 
 */



UCLASS()
class MINISHOOTER_API UShooterHUD : public UUserWidget
{
	GENERATED_BODY()

	float CurrentHealth = 0.f;
	float CurrentMaxHealth = 0.f;
	
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	ACharacterBase* Character;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	AMiniShooterHud* ShooterHud;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* LifeBar;

	UPROPERTY(EditAnywhere, meta= (BindWidget))
	UTextBlock* CurrentValueHealthText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* MaxValueHealthText;

	void BindDelegates();

	UFUNCTION()
	void UpdateHealth(const float Value);
	UFUNCTION()
	void UpdateMaxHealth(const float Value);
	
	void SetHudOwner(AMiniShooterHud* owner) {ShooterHud = owner;}
	void SetOwner(ACharacterBase* Char) { Character = Char;}
	
};
