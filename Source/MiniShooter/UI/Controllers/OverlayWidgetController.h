// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGunModeChangedSignature, const FString&, NewString);

UCLASS(BlueprintType, Blueprintable)
class MINISHOOTER_API UOverlayWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:

	virtual void BroadCastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChangedSignature;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChangedSignature;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnAmmoChangedSignature;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxAmmoChangedSignature;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnGunModeChangedSignature OnGunModeChangedSignature;
};
