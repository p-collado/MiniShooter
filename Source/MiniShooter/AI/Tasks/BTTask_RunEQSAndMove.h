// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "BTTask_RunEQSAndMove.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UBTTask_RunEQSAndMove : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RunEQSAndMove();

	FQueryFinishedSignature QueryFinishedDelegate;

	UPROPERTY(Category = EQS, EditAnywhere)
	FEQSParametrizedQueryExecutionRequest EQSRequest;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
