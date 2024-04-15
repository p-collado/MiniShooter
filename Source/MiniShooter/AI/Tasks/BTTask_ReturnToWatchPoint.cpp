// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ReturnToWatchPoint.h"

#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/AI/Components/PostingComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Tasks/AITask_MoveTo.h"

UBTTask_ReturnToWatchPoint::UBTTask_ReturnToWatchPoint()
{
	NodeName = "Return to Watch Point";
}

EBTNodeResult::Type UBTTask_ReturnToWatchPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	FReturnToWatchPointTaskMemory* MyMemory = CastInstanceNodeMemory<FReturnToWatchPointTaskMemory>(NodeMemory);
	MyMemory->MoveRequestID = FAIRequestID::InvalidRequest;
	const UPostingComponent* PostingComponent = AIController->PostingComponent;

	if (AIController && PostingComponent)
	{
		NodeResult = PerformMoveTask(OwnerComp, NodeMemory);

		return NodeResult;
	}

	NodeResult = EBTNodeResult::Failed;
	return NodeResult;
}

uint16 UBTTask_ReturnToWatchPoint::GetInstanceMemorySize() const
{
	return sizeof(FReturnToWatchPointTaskMemory);
}

EBTNodeResult::Type UBTTask_ReturnToWatchPoint::PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FReturnToWatchPointTaskMemory* MyMemory = CastInstanceNodeMemory<FReturnToWatchPointTaskMemory>(NodeMemory);
	AAIController* MyController = OwnerComp.GetAIOwner();

	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;

	if (MyController)
	{
		FAIMoveRequest MoveReq;
		MoveReq.SetNavigationFilter(*FilterClass ? FilterClass : MyController->GetDefaultNavigationFilterClass());
		MoveReq.SetAllowPartialPath(bAllowPartialPath);
		MoveReq.SetAcceptanceRadius(1.f);
		MoveReq.SetCanStrafe(bAllowStrafe);
		MoveReq.SetReachTestIncludesAgentRadius(true);
		MoveReq.SetReachTestIncludesGoalRadius(true);
		MoveReq.SetRequireNavigableEndLocation(true);
		MoveReq.SetProjectGoalLocation(true);
		MoveReq.SetUsePathfinding(true);

		UPostingComponent* PostingComponent = MyController->FindComponentByClass<UPostingComponent>();
		if (PostingComponent)
		{
			MoveReq.SetGoalLocation(PostingComponent->GetPostingPoint());
		}

		if (MoveReq.IsValid())
		{
			UAITask_MoveTo* MoveTask = MyMemory->Task.Get();
			const bool bReuseExistingTask = (MoveTask != nullptr);

			MoveTask = PrepareMoveTask(OwnerComp, MoveTask, MoveReq);

			if (MoveTask)
			{
				if (bReuseExistingTask)
				{
					if (MoveTask->IsActive())
					{
						UE_VLOG(MyController, LogBehaviorTree, Verbose, TEXT("\'%s\' reusing AITask %s"), *GetNodeName(), *MoveTask->GetName());
						MoveTask->ConditionalPerformMove();
					}
					else
					{
						UE_VLOG(MyController, LogBehaviorTree, Verbose, TEXT("\'%s\' reusing AITask %s, but task is not active - handing over move performing to task mechanics"), *GetNodeName(), *MoveTask->GetName());
					}
				}
				else
				{
					MyMemory->Task = MoveTask;
					UE_VLOG(MyController, LogBehaviorTree, Verbose, TEXT("\'%s\' task implementing move with task %s"), *GetNodeName(), *MoveTask->GetName());
					MoveTask->ReadyForActivation();
				}
				
				NodeResult = (MoveTask->GetState() != EGameplayTaskState::Finished) ? EBTNodeResult::InProgress :
					MoveTask->WasMoveSuccessful() ? EBTNodeResult::Succeeded :
					EBTNodeResult::Failed;
			}
		}
	}

	return NodeResult;
}

UAITask_MoveTo* UBTTask_ReturnToWatchPoint::PrepareMoveTask(UBehaviorTreeComponent& OwnerComp,
	UAITask_MoveTo* ExistingTask, FAIMoveRequest& MoveRequest)
{
	UAITask_MoveTo* MoveTask = ExistingTask ? ExistingTask : NewBTAITask<UAITask_MoveTo>(OwnerComp);
	if (MoveTask)
	{
		MoveTask->SetUp(MoveTask->GetAIController(), MoveRequest);
	}

	return MoveTask;
}
