// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DecreaseSuspicion.h"

#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/AI/Components/ShooterAIPerceptionComponent.h"

EBTNodeResult::Type UBTTask_DecreaseSuspicion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	const AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UShooterAIPerceptionComponent* PerceptionComponent = AIController->AIPerceptionComponent;

		if(PerceptionComponent)
		{
			PerceptionComponent->DecreaseSuspicion();
			return EBTNodeResult::InProgress;
		}
	}
	
	return EBTNodeResult::Failed;
}
