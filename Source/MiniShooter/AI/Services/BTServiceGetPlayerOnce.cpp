// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceGetPlayerOnce.h"

#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/AI/Components/ShooterAIPerceptionComponent.h"

UBTServiceGetPlayerOnce::UBTServiceGetPlayerOnce()
{
	bNotifyBecomeRelevant = true;
}

void UBTServiceGetPlayerOnce::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* Controller = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		Controller->AIPerceptionComponent->SetCurrentTargetActor(Controller->GetWorld()->GetFirstPlayerController()->GetPawn());
	}
}
