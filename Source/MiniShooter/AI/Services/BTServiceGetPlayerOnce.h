// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceGetPlayerOnce.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UBTServiceGetPlayerOnce : public UBTService
{
	GENERATED_BODY()

public:

	UBTServiceGetPlayerOnce();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
