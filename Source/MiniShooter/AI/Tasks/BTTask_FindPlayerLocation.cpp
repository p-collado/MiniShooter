// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (Player)
	{
		const FVector PlayerLocation = Player->GetActorLocation();
		
		if (SearchRandom)
		{
			FNavLocation Location;
			
			UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		
			if (NavSystem)
			{
				if (NavSystem->GetRandomPointInNavigableRadius(PlayerLocation, Radius, Location))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return  EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return  EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
