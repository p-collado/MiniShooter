// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIPerceptionComponent.h"

#include "MiniShooter/AI/ShooterAIController.h"


// Sets default values for this component's properties
UShooterAIPerceptionComponent::UShooterAIPerceptionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

EAwarenessState UShooterAIPerceptionComponent::GetCurrentAwarenessState()
{
	if (CurrentAwareness >= 0.f && CurrentAwareness <= 0.5f)
	{
		if (StateHasChange(Relaxed))
		{
			OnStateChange.ExecuteIfBound(*Cast<AShooterAIController>(GetOwner())->BehaviorTreeComponent,Relaxed);
		}
		AwarenessState = Relaxed;
		return EAwarenessState::Relaxed;
	}

	if (CurrentAwareness > 0.5f && CurrentAwareness <= 0.99f)
	{
		if (StateHasChange(Suspicious))
		{
			OnStateChange.ExecuteIfBound(*Cast<AShooterAIController>(GetOwner())->BehaviorTreeComponent,Suspicious);
		}
		AwarenessState = Suspicious;
		return EAwarenessState::Suspicious;
	}

	if (CurrentAwareness > 0.99f)
	{
		if (StateHasChange(Detection))
		{
			OnStateChange.ExecuteIfBound(*Cast<AShooterAIController>(GetOwner())->BehaviorTreeComponent,Detection);
		}
		AwarenessState = Detection;
		return EAwarenessState::Detection;
	}
	
	return InvalidState;
}

bool UShooterAIPerceptionComponent::StateHasChange(EAwarenessState NewState) const
{
	if (AwarenessState != NewState)
	{
		return true;
	}

	return false;
}


void UShooterAIPerceptionComponent::IncreaseSuspicion()
{
	if (SuspiciousTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SuspiciousTimer);
	}
	
	GetWorld()->GetTimerManager().SetTimer(SuspiciousTimer, this, &UShooterAIPerceptionComponent::IncreaseAwareness, 0.1f, true);
}

void UShooterAIPerceptionComponent::DecreaseSuspicion()
{
	if (SuspiciousTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SuspiciousTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(SuspiciousTimer, this, &UShooterAIPerceptionComponent::DecreaseAwareness, 0.1f, true);
}

void UShooterAIPerceptionComponent::ClearSuspiciousTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(SuspiciousTimer);
}

void UShooterAIPerceptionComponent::IncreaseAwareness()
{
	if (CurrentAwareness < 1.f)
	{
		CurrentAwareness += AwarenessRatio;
	}
	else
	{
		CurrentAwareness = 1.f;
		GetWorld()->GetTimerManager().ClearTimer(SuspiciousTimer);
	}
	
	Cast<AShooterAIController>(GetOwner())->BroadCastAwareness(CurrentAwareness);
}

void UShooterAIPerceptionComponent::DecreaseAwareness()
{
	if (CurrentAwareness > 0.f)
	{
		CurrentAwareness -= AwarenessRatio;
	}
	else
	{
		CurrentAwareness = 0.f;
		GetWorld()->GetTimerManager().ClearTimer(SuspiciousTimer);
	}
	
	Cast<AShooterAIController>(GetOwner())->BroadCastAwareness(CurrentAwareness);
}
