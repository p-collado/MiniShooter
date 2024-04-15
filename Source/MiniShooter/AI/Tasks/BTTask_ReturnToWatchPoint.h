// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "BTTask_ReturnToWatchPoint.generated.h"


class UAITask_MoveTo;

struct FReturnToWatchPointTaskMemory
{
	FAIRequestID MoveRequestID;
	TWeakObjectPtr<UAITask_MoveTo> Task;
};

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UBTTask_ReturnToWatchPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_ReturnToWatchPoint();
	
	UPROPERTY(Category = Node, EditAnywhere)
	TSubclassOf<UNavigationQueryFilter> FilterClass;
	
	uint32 bAllowPartialPath : 1;

	UPROPERTY(Category = Node, EditAnywhere)
	uint32 bAllowStrafe : 1;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual uint16 GetInstanceMemorySize() const override;

protected:

	virtual EBTNodeResult::Type PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual UAITask_MoveTo* PrepareMoveTask(UBehaviorTreeComponent& OwnerComp, UAITask_MoveTo* ExistingTask, FAIMoveRequest& MoveRequest);
};
