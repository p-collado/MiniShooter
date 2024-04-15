// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncreaseSuspicion.h"

#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/AI/Components/ShooterAIPerceptionComponent.h"

EBTNodeResult::Type UBTTask_IncreaseSuspicion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UShooterAIPerceptionComponent* PerceptionComponent = AIController->AIPerceptionComponent;

		if(PerceptionComponent)
		{
			PerceptionComponent->IncreaseSuspicion();
			return EBTNodeResult::InProgress;
		}
	}
	
	return EBTNodeResult::Failed;
}
