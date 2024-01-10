// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MiniShooter/AI/ShooterEnemy.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

void UEnemyHUD::NativeConstruct()
{
	Super::NativeConstruct();

	LifeBar->SetPercent(100);
	
	if(EnemyRef)
	{
		const UMiniShooterAttributeSet* Set = EnemyRef->GetAttributeSet();

		if (Set)
		{
			LifeValue->SetText(FText::AsNumber(Set->GetMaxHealth()));
			EnemyRef->OnHealthChange.AddUniqueDynamic(this, &UEnemyHUD::ChangeLifeValue);
		}
	}
}

void UEnemyHUD::ChangeLifeValue(const float NewValue)
{
	LifeBar->SetPercent(NewValue / EnemyRef->GetAttributeSet()->GetMaxHealth());
	LifeValue->SetText(FText::AsNumber(NewValue));
}
