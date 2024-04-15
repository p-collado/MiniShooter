// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "MiniShooter/GAS/MiniShooterAbilitySystemComponent.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	const UMiniShooterAttributeSet* ATS = Cast<UMiniShooterAttributeSet>(AttributeSet);
	
	OnHealthChangedSignature.Broadcast(ATS->GetHealth());
	OnMaxHealthChangedSignature.Broadcast(ATS->GetMaxHealth());
	OnAmmoChangedSignature.Broadcast(ATS->GetAmmo());
	OnMaxAmmoChangedSignature.Broadcast(ATS->GetMaxAmmo());
	OnGunModeChangedSignature.Broadcast("Single");
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	ATS->GetAmmoAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnAmmoChangedSignature.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	ATS->GetMaxAmmoAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxAmmoChangedSignature.Broadcast(Data.NewValue);
		}
	);

	UMiniShooterAbilitySystemComponent* ASC = Cast<UMiniShooterAbilitySystemComponent>(AbilitySystemComponent);
	
	ASC->OnAbilityGunModeChangedSignature.AddLambda(
		[this](const FString& String)
		{
			OnGunModeChangedSignature.Broadcast(String);
		});
}
