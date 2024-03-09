// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsSuspecting.h"

#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/AI/Components/ShooterAIPerceptionComponent.h"

UBTDecorator_IsSuspecting::UBTDecorator_IsSuspecting()
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTDecorator_IsSuspecting::OnValueChange(UBehaviorTreeComponent& BehaviorTreeComponent, bool NewValue)
{
	BehaviorTreeComponent.RequestExecution(this);
}

void UBTDecorator_IsSuspecting::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UShooterAIPerceptionComponent* AIPerceptionComponent = AIController->AIPerceptionComponent;
		if (AIPerceptionComponent)
		{
			AIPerceptionComponent->OnValueChange.BindUObject(this, &UBTDecorator_IsSuspecting::OnValueChange);
		}
	}
}

void UBTDecorator_IsSuspecting::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UShooterAIPerceptionComponent* AIPerceptionComponent = AIController->AIPerceptionComponent;
		if (AIPerceptionComponent)
		{
			AIPerceptionComponent->OnValueChange.Unbind();
		}
	}
}

bool UBTDecorator_IsSuspecting::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	
	AShooterAIController* AIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UShooterAIPerceptionComponent* AIPerceptionComponent = AIController->AIPerceptionComponent;

		if (AIPerceptionComponent)
		{
			return AIPerceptionComponent->GetIsSuspecting();
		}
	}
	
	return false;
}
