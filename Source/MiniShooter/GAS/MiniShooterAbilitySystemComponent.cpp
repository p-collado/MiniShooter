// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniShooterAbilitySystemComponent.h"

#include "Abilities/ShooterGameplayAbilityBase.h"
#include "MiniShooter/FShooterGameplayTags.h"


// Sets default values for this component's properties
UMiniShooterAbilitySystemComponent::UMiniShooterAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMiniShooterAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		if (const UShooterGameplayAbilityBase* AuraGameplayAbility =  Cast<UShooterGameplayAbilityBase>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraGameplayAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
	bStartupAbilitiesGiven = true;
}

void UMiniShooterAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UMiniShooterAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UMiniShooterAbilitySystemComponent::ChangePistolGunMode()
{
	FScopedAbilityListLock ActiveScopeList(*this);
	const FGameplayTag InputTag = FShooterGameplayTags::Get().Input_LMB;
	FGameplayAbilitySpec FoundAbility;

	for (FGameplayAbilitySpec& AbilitySpecInASC : GetActivatableAbilities())
	{
		if(Cast<UShooterGameplayAbilityBase>(AbilitySpecInASC.Ability)->StartupInputTag.MatchesTagExact(InputTag))
		{
			FoundAbility = AbilitySpecInASC;
			break;
		}
	}

	FGameplayAbilitySpec AbilitySpec;
	const UShooterGameplayAbilityBase* Ability = nullptr;

	if (Cast<UShooterGameplayAbilityBase>(FoundAbility.Ability)->GunMode == "Single")
	{
		AbilitySpec = FGameplayAbilitySpec(ModeAuto, 1);
		AbilitySpec.DynamicAbilityTags.AddTag(InputTag);
		Ability = Cast<UShooterGameplayAbilityBase>(AbilitySpec.Ability);
		GiveAbility(AbilitySpec);
	}
	else if (Cast<UShooterGameplayAbilityBase>(FoundAbility.Ability)->GunMode == "Auto")
	{
		AbilitySpec = FGameplayAbilitySpec(ModeSingle, 1);
		AbilitySpec.DynamicAbilityTags.AddTag(InputTag);
		Ability = Cast<UShooterGameplayAbilityBase>(AbilitySpec.Ability);
		GiveAbility(AbilitySpec);
	}
	
	if(FoundAbility.Handle.IsValid())
	{
		ClearAbility(FoundAbility.Handle);
	}

	OnAbilityGunModeChangedSignature.Broadcast(Ability->GunMode);
}

FGameplayTag UMiniShooterAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag Tag : AbilitySpec.DynamicAbilityTags)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))))
		{
			return Tag;
		}
	}

	return FGameplayTag();
}

