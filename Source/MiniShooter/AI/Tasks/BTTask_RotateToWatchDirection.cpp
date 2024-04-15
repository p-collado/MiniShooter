// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RotateToWatchDirection.h"

#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/AI/Components/PostingComponent.h"

UBTTask_RotateToWatchDirection::UBTTask_RotateToWatchDirection()
{
	NodeName = "Rotate To Watch Direction";
}

EBTNodeResult::Type UBTTask_RotateToWatchDirection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	const AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	const UPostingComponent* PostingComponent = AIController->PostingComponent;

	if (AIController && PostingComponent)
	{
		const FRotator FacingRotator = PostingComponent->GetDirection().Rotation();
		AIController->GetPawn()->SetActorRotation(FacingRotator, ETeleportType::None);
		Result = EBTNodeResult::Succeeded;
	}

	return Result;
}
