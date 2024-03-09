// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsSuspecting.generated.h"

/**
 * 
 */

UCLASS()
class MINISHOOTER_API UBTDecorator_IsSuspecting : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsSuspecting();

	void OnValueChange(UBehaviorTreeComponent& BehaviorTreeComponent, bool NewValue);
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
