// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "ShooterAIPerceptionComponent.generated.h"

UENUM(BlueprintType)
enum EAwarenessState
{
	InvalidState,
	Relaxed,
	Suspicious,
	Detection
};

DECLARE_DELEGATE_TwoParams(FOnIsSuspicionValueChange, UBehaviorTreeComponent&, bool);
DECLARE_DELEGATE_TwoParams(FOnEnemyStateValueChange, UBehaviorTreeComponent&, EAwarenessState);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINISHOOTER_API UShooterAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UShooterAIPerceptionComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	EAwarenessState GetCurrentAwarenessState();

	bool StateHasChanged(EAwarenessState NewState) const;
	
	FOnIsSuspicionValueChange OnValueChange;
	FOnEnemyStateValueChange OnStateChange;

	float GetCurrentAwarenessStateFromAwarenessLevel() const { return CurrentAwareness; }
	bool GetIsSuspecting() const { return bBeSuspecting; }
	AActor* GetActorTarget() const { return CurrentTargetActor; }
	FVector GetLastPlayerPosition() const { return LastPlayerPosition; }
	EAwarenessState GetCurrentAwarenessState() const { return AwarenessState; }

	void SetCurrentTargetActor(AActor* TargetActor) { CurrentTargetActor = TargetActor;	}
	void SetCurrentAwareness(float NewAwareness) { CurrentAwareness = NewAwareness; }
	void SetIsSuspecting(bool NewBool) { bBeSuspecting = NewBool; }
	void SetLastPlayerPosition(const FVector& LastPosition);

	void IncreaseSuspicion();
	void DecreaseSuspicion();
	void ClearSuspiciousTimer();
	void PauseSuspiciousTimer();
	void ResumeSuspiciousTimer();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Perception")
	bool bBeSuspecting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Perception")
	AActor* CurrentTargetActor = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Perception")
	float CurrentAwareness = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Perception")
	float AwarenessRatio = 0.025f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle SuspiciousTimer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Perception")
	TEnumAsByte<EAwarenessState> AwarenessState = Relaxed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Perception")
	FVector LastPlayerPosition;

private:
	
	void IncreaseAwareness();
	void DecreaseAwareness();
	
};
