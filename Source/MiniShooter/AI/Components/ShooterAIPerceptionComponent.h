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

DECLARE_DELEGATE_TwoParams(FOnValueChange, UBehaviorTreeComponent&, bool);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINISHOOTER_API UShooterAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UShooterAIPerceptionComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	EAwarenessState GetCurrentAwarenessState() const;
	
	FOnValueChange OnValueChange;

	float GetCurrentAwareness() const { return CurrentAwareness; }
	bool GetIsSuspecting() const { return bBeSuspecting; }
	AActor* GetActorTarget() const { return CurrentTargetActor; }

	void SetCurrentTargetActor(AActor* TargetActor) { CurrentTargetActor = TargetActor;	}
	void SetCurrentAwareness(float NewAwareness) { CurrentAwareness = NewAwareness; }
	void SetIsSuspecting(bool NewBool) { bBeSuspecting = NewBool; }

	void IncreaseSuspicion();
	void DecreaseSuspicion();
	void ClearSuspiciousTimer();

protected:

	UPROPERTY(VisibleAnywhere, Category= "Perception")
	bool bBeSuspecting;

	UPROPERTY(VisibleAnywhere, Category= "Perception")
	AActor* CurrentTargetActor = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category= "Perception")
	float CurrentAwareness = 0.f;

	UPROPERTY(EditAnywhere, Category= "Perception")
	float AwarenessRatio = 0.025f;

	UPROPERTY()
	FTimerHandle SuspiciousTimer;
	
	UPROPERTY(VisibleAnywhere, Category= "Perception")
	TEnumAsByte<EAwarenessState> AwarenessState = Relaxed;

private:
	
	void IncreaseAwareness();
	void DecreaseAwareness();
	
};
