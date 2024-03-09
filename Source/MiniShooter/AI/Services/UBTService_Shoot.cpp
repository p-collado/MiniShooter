// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTService_Shoot.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MiniShooter/AI/ShooterAIController.h"

UUBTService_Shoot::UUBTService_Shoot(FObjectInitializer const& ObjectInitializer) : UBTService_BlackboardBase{ObjectInitializer}
{
	NodeName = "Shoot";
	bNotifyBecomeRelevant = true;
}

void UUBTService_Shoot::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	AShooterAIController* const AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		AIController->SetFocus(Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("TargetActor")), EAIFocusPriority::Default);
		AIController->Shoot();
	}
}
