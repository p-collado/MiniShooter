// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MiniShooterAbilitySystemComponent.generated.h"

/**
 * Custom Ability System Component
 * @param ModeAuto Reference to mode-auto ability.
 * @param ModeSingle Reference to mode-single ability.
 */

class UShooterGameplayAbilityBase;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityGunModeChangedSignature, const FString&);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINISHOOTER_API UMiniShooterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMiniShooterAbilitySystemComponent();

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	//Input Execution Tag
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable)
	void ChangePistolGunMode();

	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	//Delegate
	FOnAbilityGunModeChangedSignature OnAbilityGunModeChangedSignature;

	UPROPERTY(EditDefaultsOnly, Category="GAS|AbilityPistolConfig")
	TSubclassOf<UShooterGameplayAbilityBase> ModeAuto;

	UPROPERTY(EditDefaultsOnly, Category="GAS|AbilityPistolConfig")
	TSubclassOf<UShooterGameplayAbilityBase> ModeSingle;
	
	bool bStartupAbilitiesGiven = false;
};
