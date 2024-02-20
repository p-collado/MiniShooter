// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "MiniShooter/Character/ShooterEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MiniShooter/Character/CharacterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AShooterAIController::AShooterAIController(FObjectInitializer const& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AI percception
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	
	//Sight Sense
	AIConfigSightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSenseComp"));

	//Hear Sense
	AIConfigHearingSense = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingSenseComp"));
	
	SetupPerceptionSystem();
}

// Called when the game starts or when spawned
void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterAIController::Shoot()
{
	AShooterEnemy* Enemy = Cast<AShooterEnemy>(GetPawn());
	
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		UseBlackboard(BehaviorTree->BlackboardAsset.Get(), BlackboardComponent);
		RunBehaviorTree(BehaviorTree);
		BlackboardComponent->SetValueAsEnum("CurrentEnemyState", EnemyState::Idle);
	}
}

void AShooterAIController::SetupPerceptionSystem()
{
	if (AIPerceptionComponent)
	{
		SetPerceptionComponent(*AIPerceptionComponent);

		if (AIConfigSightSense)
		{
			AIConfigSightSense->SightRadius = 500.f;
			AIConfigSightSense->LoseSightRadius = AIConfigSightSense->SightRadius + 25.f;
			AIConfigSightSense->PeripheralVisionAngleDegrees = 90.f;
			AIConfigSightSense->SetMaxAge(5.f);
			AIConfigSightSense->AutoSuccessRangeFromLastSeenLocation = 520.f;
			AIConfigSightSense->DetectionByAffiliation.bDetectEnemies = true;
			AIConfigSightSense->DetectionByAffiliation.bDetectFriendlies = true;
			AIConfigSightSense->DetectionByAffiliation.bDetectNeutrals = true;

			AIPerceptionComponent->SetDominantSense(*AIConfigSightSense->GetSenseImplementation());
			AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AShooterAIController::OnTargetDetected);
			AIPerceptionComponent->ConfigureSense(*AIConfigSightSense);
		}
	}
}

void AShooterAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	ACharacterBase* const Char = Cast<ACharacterBase>(Actor);
	
	if (Char)
	{
		BlackboardComponent->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
		
		if (Stimulus.WasSuccessfullySensed())
		{
			BlackboardComponent->SetValueAsEnum("CurrentEnemyState", EnemyState::Combat);
			BlackboardComponent->SetValueAsObject("TargetActor", Actor);
		}
		else
		{
			BlackboardComponent->SetValueAsEnum("CurrentEnemyState", EnemyState::Idle);
			BlackboardComponent->SetValueAsObject("TargetActor", nullptr);
		}
	}
}
