// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MiniShooterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UMiniShooterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


public:
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMiniShooterAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMiniShooterAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData Ammo;
	ATTRIBUTE_ACCESSORS(UMiniShooterAttributeSet, Ammo)

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(UMiniShooterAttributeSet, MaxAmmo)

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Movement")
	FGameplayAttributeData MovSpeed;
	ATTRIBUTE_ACCESSORS(UMiniShooterAttributeSet, MovSpeed)
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Movement")
	FGameplayAttributeData MaxMovSpeed;
	ATTRIBUTE_ACCESSORS(UMiniShooterAttributeSet, MaxMovSpeed)

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Movement")
	FGameplayAttributeData CrouchSpeed;
	ATTRIBUTE_ACCESSORS(UMiniShooterAttributeSet, CrouchSpeed)
};
