// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrementPathIndex.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MiniShooter/AI/PatrolPath.h"
#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/Character/ShooterEnemy.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* const AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	
	if (AIController)
	{
		AShooterEnemy* const Char = Cast<AShooterEnemy>(AIController->GetPawn());
		
		if (Char)
		{
			auto* const Blackboard = OwnerComp.GetBlackboardComponent();

			if (Blackboard)
			{
				int32 const NumPoints = Char->PatrolPath->Num();
				int32 const MinIndex = 0;
				int32 const MaxIndex = NumPoints - 1;
				int32 CurrentIndex = Blackboard->GetValueAsInt(GetSelectedBlackboardKey());

				if (bBiDirectional)
				{
					if (CurrentIndex >= MaxIndex && Direction == EDirection::Forward)
					{
						Direction = EDirection::Reverse;
					}
					else if(CurrentIndex == MinIndex && Direction == EDirection::Reverse)
					{
						Direction = EDirection::Forward;
					}
				}

				Blackboard->SetValueAsInt(GetSelectedBlackboardKey(), (Direction == EDirection::Forward ? ++CurrentIndex : --CurrentIndex) % NumPoints);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
