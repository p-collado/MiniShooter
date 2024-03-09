// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTreeComponent;
class UAttributeSet;
class UAbilitySystemComponent;
struct FAIStimulus;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
class UShooterAIPerceptionComponent;
class UBehaviorTree;
class UBlackboardComponent;

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
	// Sets default values for this actor's properties
	AShooterAIController(FObjectInitializer const& ObjectInitializer);

	void OnGetShot() const;

	UPROPERTY(BlueprintAssignable) //Delegate to notify enemy has been shot
	FOnGetShotSignature OnGetShotSignature;

	UPROPERTY(BlueprintAssignable)
	FOnGettingSuspiciousSignature OnGettingSuspiciousSignature;

	void BroadCastAwareness(float CurrentAwareness);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(VisibleAnywhere, Category= "GAS");
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category= "GAS")
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Shoot();
	
	UPROPERTY(EditAnywhere, Category= "AIConfig")
	TObjectPtr<UShooterAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditAnywhere, Category= "AIConfig")
	TObjectPtr<UAISenseConfig_Sight> AIConfigSightSense;

	UPROPERTY(EditAnywhere, Category= "AIConfig")
	TObjectPtr<UAISenseConfig_Hearing> AIConfigHearingSense;
	
	UPROPERTY(EditAnywhere, Category= "AIConfig")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, Category= "AIConfig")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, Category= "AIConfig")
	UBlackboardComponent* BlackboardComponent;
};
