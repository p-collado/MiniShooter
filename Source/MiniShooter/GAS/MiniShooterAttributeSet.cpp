// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniShooterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include <MiniShooter/Interaction/CombatInterface.h>
#include <AbilitySystemBlueprintLibrary.h>
#include "GameFramework/Character.h"
#include "MiniShooter/Player/ShooterPlayerController.h"

void UMiniShooterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	HarvestGameplayEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetAmmoAttribute())
	{
		SetAmmo(FMath::Clamp(GetAmmo(), 0.f, GetMaxAmmo()));
	}

	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		if (GetHealth() <= 0.f)
		{
			ICombatInterface* CombatInterface = Cast<ICombatInterface>(Data.Target.GetAvatarActor());
		
			if (CombatInterface)
			{
				CombatInterface->Die();
			}
		}
		const float LocalIncomingDamage = GetIncomingDamage();
		ShowFloatingText(Props, LocalIncomingDamage, false, false);
	}
}

void UMiniShooterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetAmmoAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxAmmo());
	}
}

void UMiniShooterAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		AShooterPlayerController* PC = Cast<AShooterPlayerController>(Props.SourceCharacter->Controller);
		if (PC)
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
			return;
		}

		PC = Cast<AShooterPlayerController>(Props.TargetCharacter->Controller);
		if (PC)
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
		}
	}
}

void UMiniShooterAttributeSet::HarvestGameplayEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.AvatarSource = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.AvatarSource != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.AvatarSource))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.AvatarTarget = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.AvatarTarget);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.AvatarTarget);
	}
}
