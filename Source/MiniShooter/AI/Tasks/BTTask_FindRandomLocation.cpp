// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MiniShooter/AI/ShooterAIController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Find random location in radius");
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* const AIcontroller = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	
	if (AIcontroller)
	{
		auto* const Pawn = AIcontroller->GetPawn();
		
		if (Pawn)
		{
			//FVector Origin = Pawn->GetActorLocation();

			UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

			if (NavSystem)
			{
				FNavLocation Location;
				int Counter = 0;

				do
				{
					if (NavSystem->GetRandomPointInNavigableRadius(OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()), Radius, Location))
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", Location.Location);
					}
					++Counter;
				}
				while ((OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()) - Location.Location).SquaredLength() < MinimunRadius*MinimunRadius && MinimunRadius != 0.f && Counter < 10);
				
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
