// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "ShooterAIController.generated.h"

class UPostingComponent;
class UBehaviorTreeComponent;
class UAttributeSet;
class UAbilitySystemComponent;
struct FAIStimulus;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
class UShooterAIPerceptionComponent;
class UBehaviorTree;
class UBlackboardComponent;

//Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGetShotSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGettingSuspiciousSignature, float, AwarenessPercent);

UCLASS()
class MINISHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

public:
	AShooterAIController(FObjectInitializer const& ObjectInitializer);

	void OnGetShot() const;

	UPROPERTY(BlueprintAssignable) //Delegate to notify enemy has been shot
	FOnGetShotSignature OnGetShotSignature;

	UPROPERTY(BlueprintAssignable)
	FOnGettingSuspiciousSignature OnGettingSuspiciousSignature;

	void BroadCastAwareness(float CurrentAwareness);
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(VisibleAnywhere, Category= "GAS");
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category= "GAS")
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Shoot();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category= "AIConfig")
	TObjectPtr<UShooterAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "AIConfig")
	TObjectPtr<UAISenseConfig_Sight> AIConfigSightSense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "AIConfig")
	TObjectPtr<UAISenseConfig_Hearing> AIConfigHearingSense;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "AIConfig")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "AIConfig")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Posting and Patrol Config")
	TObjectPtr<UPostingComponent> PostingComponent;
	
	UPROPERTY(EditAnywhere, Category= "AIConfig")
	UBlackboardComponent* BlackboardComponent;
};
