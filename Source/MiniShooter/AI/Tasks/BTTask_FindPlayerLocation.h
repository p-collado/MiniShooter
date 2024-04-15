// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlayerLocation.generated.h"

/**
 * 
 */

class UAITask_MoveTo;

struct FMoveToTaskMemory
{
	FAIRequestID MoveRequestID;
	TWeakObjectPtr<UAITask_MoveTo> Task;
};

UCLASS()
class MINISHOOTER_API UBTTask_FindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config", meta=(AllowPrivateAccess = true))
	bool SearchRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config", meta=(AllowPrivateAccess = true, EditCondition= "SearchRandom"))
	float Radius = 150.f;

public:
	UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer);

	UPROPERTY(Category = Node, EditAnywhere)
	TSubclassOf<UNavigationQueryFilter> FilterClass;

	uint32 bAllowPartialPath : 1;

	UPROPERTY(Category = Node, EditAnywhere)
	uint32 bAllowStrafe : 1;

	virtual uint16 GetInstanceMemorySize() const override;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, bool RandomSearch);
	virtual UAITask_MoveTo* PrepareMoveTask(UBehaviorTreeComponent& OwnerComp, UAITask_MoveTo* ExistingTask, FAIMoveRequest& MoveRequest);
};
