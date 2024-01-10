// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterHUD.h"
#include "MiniShooter/Character/CharacterBase.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UShooterHUD::NativeConstruct()
{
	Super::NativeConstruct();

	LifeBar->PercentDelegate.BindUFunction(this, "SetLifeBarPercent");
	CurrentValueHealthText->SetText(FText::FromString("0"));
	MaxValueHealthText->SetText(FText::FromString("0"));
	LifeBar->SetPercent(0.f);
}