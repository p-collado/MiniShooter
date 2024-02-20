// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPathPoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MiniShooter/AI/PatrolPath.h"
#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/Character/ShooterEnemy.h"

UBTTask_FindPatrolPathPoint::UBTTask_FindPatrolPathPoint(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UBTTask_FindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* const AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	
	if (AIController)
	{
		auto* const Blackboard = OwnerComp.GetBlackboardComponent();

		if (Blackboard)
		{
			int32 index = Blackboard->GetValueAsInt(GetSelectedBlackboardKey());

			AShooterEnemy* Pawn = Cast<AShooterEnemy>(AIController->GetPawn());

			if (Pawn)
			{
				APatrolPath* PathPtr = Pawn->PatrolPath;

				if (PathPtr)
				{
					FVector Point = PathPtr->GetPatrolPoint(index);

					FVector Global = PathPtr->GetActorTransform().TransformPosition(Point);

					Blackboard->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, Global);

					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
