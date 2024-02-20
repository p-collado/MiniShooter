// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterHUD.h"

#include "MiniShooterHud.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UShooterHUD::BindDelegates()
{
	ShooterHud->OnHealthChange.AddUniqueDynamic(this, &UShooterHUD::UpdateHealth);
	ShooterHud->OnMaxHealthChange.AddUniqueDynamic(this, &UShooterHUD::UpdateMaxHealth);
}

void UShooterHUD::UpdateHealth(const float Value)
{
	CurrentHealth = Value;
	LifeBar->SetPercent(CurrentMaxHealth <= 0.f ? 0.f : Value / CurrentMaxHealth);
	CurrentValueHealthText->SetText(FText::AsNumber(Value));
}

void UShooterHUD::UpdateMaxHealth(const float Value)
{
	CurrentMaxHealth = Value;
	LifeBar->SetPercent( Value <= 0.f ? 0.f : CurrentHealth / Value);
	MaxValueHealthText->SetText(FText::AsNumber(Value));
}
