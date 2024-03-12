// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetFocus.h"
#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/AI/Components/ShooterAIPerceptionComponent.h"

EBTNodeResult::Type UBTTask_SetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AShooterAIController* Controller =  Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		Controller->SetFocus(Controller->AIPerceptionComponent->GetActorTarget(), EAIFocusPriority::Default);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
