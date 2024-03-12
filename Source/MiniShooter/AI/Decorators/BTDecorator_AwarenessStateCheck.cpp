// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_AwarenessStateCheck.h"

#include "MiniShooter/AI/ShooterAIController.h"

UBTDecorator_AwarenessStateCheck::UBTDecorator_AwarenessStateCheck()
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTDecorator_AwarenessStateCheck::OnValueChange(UBehaviorTreeComponent& BehaviorTreeComponent, EAwarenessState NewState)
{
	BehaviorTreeComponent.RequestExecution(this);
}

void UBTDecorator_AwarenessStateCheck::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UShooterAIPerceptionComponent* AIPerceptionComponent = AIController->AIPerceptionComponent;
		if (AIPerceptionComponent)
		{
			AIPerceptionComponent->OnStateChange.BindUObject(this, &UBTDecorator_AwarenessStateCheck::OnValueChange);
		}
	}
}

void UBTDecorator_AwarenessStateCheck::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UShooterAIPerceptionComponent* AIPerceptionComponent = AIController->AIPerceptionComponent;
		if (AIPerceptionComponent)
		{
			AIPerceptionComponent->OnStateChange.Unbind();
		}
	}
}

bool UBTDecorator_AwarenessStateCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		const EAwarenessState CurrentAwarenessState = AIController->AIPerceptionComponent->GetCurrentAwarenessState();

		if (CurrentAwarenessState == AwarenessStateToCompare)
		{
			return true;
		}
	}

	return false;
}
