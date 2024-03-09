// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetEnemyState.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetEnemyState::UBTTask_SetEnemyState(FObjectInitializer const& ObjectInitializer)
{
	NodeName = FString("SetEnemyState");
}

EBTNodeResult::Type UBTTask_SetEnemyState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto* const Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(BlackboardKey.SelectedKeyName, State.GetIntValue());
	}

	return EBTNodeResult::Succeeded;
}
