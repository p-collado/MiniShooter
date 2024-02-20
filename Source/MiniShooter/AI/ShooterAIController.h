// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "ShooterAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
class UAIPerceptionComponent;
class UBehaviorTree;
class UBlackboardComponent;

UENUM()
enum EnemyState
{
	Invalid,
	Idle,
	Alert,
	Combat
};

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Shoot();
	
	UPROPERTY(EditAnywhere, Category= "AIConfig")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, Category= "AIConfig")
	UAISenseConfig_Sight* AIConfigSightSense;

	UPROPERTY(EditAnywhere, Category= "AIConfig")
	UAISenseConfig_Hearing* AIConfigHearingSense;
	
	UPROPERTY(EditAnywhere, Category= "AIConfig")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category= "AIConfig")
	UBlackboardComponent* BlackboardComponent;
};
