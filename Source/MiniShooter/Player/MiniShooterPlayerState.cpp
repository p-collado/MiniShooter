// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniShooter/Player/MiniShooterPlayerState.h"

#include "MiniShooter/GAS/MiniShooterAbilitySystemComponent.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

AMiniShooterPlayerState::AMiniShooterPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMiniShooterAbilitySystemComponent>("AbilitySystemCmp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMiniShooterAttributeSet>(TEXT("AttributeCharacterList"));
}

UAbilitySystemComponent* AMiniShooterPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
