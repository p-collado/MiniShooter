// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MiniShooter/AI/Components/ShooterAIPerceptionComponent.h"
#include "BTTask_SetEnemyState.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UBTTask_SetEnemyState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAwarenessState> State;

	UBTTask_SetEnemyState(FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
