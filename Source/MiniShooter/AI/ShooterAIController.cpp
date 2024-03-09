// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "AbilitySystemComponent.h"
#include "MiniShooter/Character/ShooterEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ShooterAIPerceptionComponent.h"
#include "MiniShooter/Character/PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AShooterAIController::AShooterAIController(FObjectInitializer const& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AI percception
	AIPerceptionComponent = CreateDefaultSubobject<UShooterAIPerceptionComponent>(TEXT("PerceptionShooterComponent"));
	
	//Sight Sense
	AIConfigSightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSenseComp"));

	//Hear Sense
	AIConfigHearingSense = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingSenseComp"));

	//TreeCmp
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTreeCmp"));
	
	SetupPerceptionSystem();
}

void AShooterAIController::BroadCastAwareness(float CurrentAwareness)
{
	OnGettingSuspiciousSignature.Broadcast(CurrentAwareness);
}

// Called when the game starts or when spawned
void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Cast<UMiniShooterAttributeSet>(AttributeSet)->GetHealthAttribute()).AddUObject(this, &AShooterAIController::OnGetShot);
}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterAIController::Shoot()
{
	AShooterEnemy* Enemy = Cast<AShooterEnemy>(GetPawn());
	
	if(Enemy)
	{
		Enemy->GetAbilitySystemComponent()->AbilityLocalInputPressed(26);
	}
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		UseBlackboard(BehaviorTree->BlackboardAsset.Get(), BlackboardComponent);
		RunBehaviorTree(BehaviorTree);
		BlackboardComponent->SetValueAsEnum("CurrentEnemyState", EAwarenessState::Relaxed);
	}

	AShooterEnemy* OwnerPawn = Cast<AShooterEnemy>(InPawn);

	if (OwnerPawn)
	{
		AbilitySystemComponent = OwnerPawn->GetAbilitySystemComponent();
		AttributeSet = OwnerPawn->GetAttributeSet();
	}
}

void AShooterAIController::OnGetShot() const
{
	BlackboardComponent->SetValueAsEnum("CurrentEnemyState", EAwarenessState::Detection);
	BlackboardComponent->SetValueAsBool("Alert", true);
	AIPerceptionComponent->SetCurrentAwareness(1.f);
	OnGetShotSignature.Broadcast();
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
			AIConfigSightSense->PeripheralVisionAngleDegrees = 50.f;
			AIConfigSightSense->SetMaxAge(2.f);
			AIConfigSightSense->AutoSuccessRangeFromLastSeenLocation = 15.f;
			AIConfigSightSense->DetectionByAffiliation.bDetectEnemies = true;
			AIConfigSightSense->DetectionByAffiliation.bDetectFriendlies = true;
			AIConfigSightSense->DetectionByAffiliation.bDetectNeutrals = true;

			AIPerceptionComponent->SetDominantSense(*AIConfigSightSense->GetSenseImplementation());
			AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AShooterAIController::OnTargetDetected);
			AIPerceptionComponent->ConfigureSense(*AIConfigSightSense);
		}
	}

	BrainComponent = BehaviorTreeComponent;
}

void AShooterAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	APlayerCharacter* const Char = Cast<APlayerCharacter>(Actor);
	
	if (Char)
	{
		// BlackboardComponent->SetValueAsBool("PlayerDetected", Stimulus.WasSuccessfullySensed());
		//
		// if (Stimulus.WasSuccessfullySensed())
		// {
		// 	BlackboardComponent->SetValueAsEnum("CurrentEnemyState", EEnemyState::Combat);
		// 	BlackboardComponent->SetValueAsObject("TargetActor", Actor);
		// 	BlackboardComponent->SetValueAsBool("Alert", true);
		// }
		// else
		// {
		// 	BlackboardComponent->SetValueAsEnum("CurrentEnemyState", EEnemyState::Alert);
		// 	BlackboardComponent->SetValueAsObject("TargetActor", nullptr);
		// 	BlackboardComponent->SetValueAsVector("TargetLocation", Actor->GetActorLocation());
		// }

		if (Stimulus.WasSuccessfullySensed())
		{
			if (AIPerceptionComponent->GetCurrentAwarenessState() != Detection)
			{
				AIPerceptionComponent->SetCurrentTargetActor(Actor);
				AIPerceptionComponent->IncreaseSuspicion();
				AIPerceptionComponent->SetIsSuspecting(true);
				AIPerceptionComponent->OnValueChange.ExecuteIfBound(*BehaviorTreeComponent, AIPerceptionComponent->GetIsSuspecting());
			}
		}
		else
		{
			if (AIPerceptionComponent->GetCurrentAwarenessState() == Detection)
			{
				
			}
			else
			{
				AIPerceptionComponent->SetCurrentTargetActor(nullptr);
				AIPerceptionComponent->DecreaseSuspicion();
				AIPerceptionComponent->SetIsSuspecting(false);
				AIPerceptionComponent->OnValueChange.ExecuteIfBound(*BehaviorTreeComponent, AIPerceptionComponent->GetIsSuspecting());
			}
		}
	}
}
