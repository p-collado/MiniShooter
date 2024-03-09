// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_AwarenessStateCheck.h"

#include "MiniShooter/AI/ShooterAIController.h"

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
