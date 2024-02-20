// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UBTService_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UUBTService_Shoot : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UUBTService_Shoot(FObjectInitializer const& ObjectInitializer);
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
