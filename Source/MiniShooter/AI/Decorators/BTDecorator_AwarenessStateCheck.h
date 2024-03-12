// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MiniShooter/AI/Components/ShooterAIPerceptionComponent.h"
#include "BTDecorator_AwarenessStateCheck.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UBTDecorator_AwarenessStateCheck : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_AwarenessStateCheck();

	void OnValueChange(UBehaviorTreeComponent& BehaviorTreeComponent, EAwarenessState);
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAwarenessState> AwarenessStateToCompare;
};
