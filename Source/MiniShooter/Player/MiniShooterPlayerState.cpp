// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniShooter/Player/MiniShooterPlayerState.h"

#include "AbilitySystemComponent.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

AMiniShooterPlayerState::AMiniShooterPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemCmp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMiniShooterAttributeSet>(TEXT("AttributeCharacterList"));
}

UAbilitySystemComponent* AMiniShooterPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
