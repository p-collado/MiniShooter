// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RunEQSAndMove.h"

#include "BehaviorTree/Tasks/BTTask_RunEQSQuery.h"

UBTTask_RunEQSAndMove::UBTTask_RunEQSAndMove()
{
	NodeName = "Run EQS and Move";
}

EBTNodeResult::Type UBTTask_RunEQSAndMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* QueryOwner = OwnerComp.GetOwner();
	AController* ControllerOwner = Cast<AController>(QueryOwner);
	if (ControllerOwner)
	{
		QueryOwner = ControllerOwner->GetPawn();
	}

	if (QueryOwner && EQSRequest.IsValid())
	{
		const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		FBTEnvQueryTaskMemory* MyMemory = CastInstanceNodeMemory<FBTEnvQueryTaskMemory>(NodeMemory);

		MyMemory->RequestID = EQSRequest.Execute(*QueryOwner, BlackboardComponent, QueryFinishedDelegate);
		
		const bool bValid = (MyMemory->RequestID >= 0);
		if (bValid)
		{
			WaitForMessage(OwnerComp, UBrainComponent::AIMessage_QueryFinished, MyMemory->RequestID);
			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}
