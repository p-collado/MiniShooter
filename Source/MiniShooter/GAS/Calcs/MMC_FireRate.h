// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_FireRate.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UMMC_FireRate : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	FGameplayEffectAttributeCaptureDefinition FireRateDef;

public:

	UMMC_FireRate();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};