// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTAsk_ChasePlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MiniShooter/AI/ShooterAIController.h"

UBTTAsk_ChasePlayer::UBTTAsk_ChasePlayer(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase {ObjectInitializer}
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTAsk_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* const AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	
	if (AIController)
	{
		FVector PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		AIController->MoveToLocation(PlayerLocation, 200.f);

		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
