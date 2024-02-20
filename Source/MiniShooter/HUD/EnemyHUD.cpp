// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MiniShooter/Character/ShooterEnemy.h"

void UEnemyHUD::SetCurrentMaxLife(float Value)
{
	CurrentMaxLife = Value;
}

void UEnemyHUD::BindDelegates()
{
	EnemyRef->OnHealthChange.AddUniqueDynamic(this, &UEnemyHUD::ChangeLifeValue);
}

void UEnemyHUD::ChangeLifeValue(const float NewValue)
{
	CurrentLife = NewValue;
	LifeBar->SetPercent(CurrentLife / CurrentMaxLife);
	LifeValue->SetText(FText::AsNumber(CurrentLife));
}
