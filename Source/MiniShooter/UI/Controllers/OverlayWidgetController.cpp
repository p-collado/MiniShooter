// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	UMiniShooterAttributeSet* ATS = Cast<UMiniShooterAttributeSet>(AttributeSet);
	OnHealthChangedSignature.Broadcast(ATS->GetHealth());
	OnMaxHealthChangedSignature.Broadcast(ATS->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UMiniShooterAttributeSet* ATS = Cast<UMiniShooterAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	ATS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChangedSignature.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	ATS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChangedSignature.Broadcast(Data.NewValue);
		}
	);
}
