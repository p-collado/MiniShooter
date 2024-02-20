// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"

#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/Character/CharacterBase.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed(FObjectInitializer const& ObjectInitializer) : UBTService_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Change Speed Service");
	bNotifyBecomeRelevant = true;
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AShooterAIController* const AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	
	if (AIController)
	{
		ACharacterBase* const Char = Cast<ACharacterBase>(AIController->GetPawn());
		
		if (Char)
		{
			Cast<UMiniShooterAttributeSet>(Char->GetAttributeSet())->SetMovSpeed(Speed);
		}
	}
}
