// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniShooter/GAS/Calcs/MMC_FireRate.h"

#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

UMMC_FireRate::UMMC_FireRate()
{
	FireRateDef.AttributeToCapture = UMiniShooterAttributeSet::GetFireRateAttribute();
	FireRateDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	FireRateDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(FireRateDef);
}

float UMMC_FireRate::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.TargetTags = TargetTags;
	float CurrentFireRate = 0.f;
	GetCapturedAttributeMagnitude(FireRateDef, Spec, EvaluationParameters, CurrentFireRate);
	
	if(CurrentFireRate <= 0)
	{
		CurrentFireRate = 2.f; //Default Value
	}
	
	CurrentFireRate = 1.f/CurrentFireRate;
	return CurrentFireRate;
}
