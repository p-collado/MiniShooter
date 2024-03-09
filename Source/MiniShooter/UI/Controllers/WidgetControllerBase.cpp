// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetControllerBase.h"

void UWidgetControllerBase::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UWidgetControllerBase::BroadCastInitialValues()
{
	
}

void UWidgetControllerBase::BindCallbacksToDependencies()
{
	
}
