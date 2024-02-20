// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTService_Shoot.h"

#include "AbilitySystemComponent.h"
#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/Character/ShooterEnemy.h"

UUBTService_Shoot::UUBTService_Shoot(FObjectInitializer const& ObjectInitializer) : UBTService_BlackboardBase{ObjectInitializer}
{
	NodeName = "Shoot";
	bNotifyBecomeRelevant = true;
}

void UUBTService_Shoot::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	AShooterAIController* const AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		AShooterEnemy* const Char = Cast<AShooterEnemy>(AIController->GetPawn());

		if (Char)
		{
			Char->GetAbilitySystemComponent()->AbilityLocalInputPressed(26);
		}
	}
}
