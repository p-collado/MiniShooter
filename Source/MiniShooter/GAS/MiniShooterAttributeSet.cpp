// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniShooterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

void UMiniShooterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
  Super::PostGameplayEffectExecute(Data);

  if (Data.EvaluatedData.Attribute == GetHealthAttribute())
  {

  }
}
