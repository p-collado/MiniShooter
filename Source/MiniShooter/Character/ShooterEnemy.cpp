// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "MiniShooter/AI/ShooterAIController.h"
#include "MiniShooter/AI/Components/ShooterAIPerceptionComponent.h"
#include "MiniShooter/Character/Components/ShooterCharacterMovement.h"
#include "MiniShooter/GAS/MiniShooterAbilitySystemComponent.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"
#include "MiniShooter/UI/Widgets/ShooterUserWidget.h"

// Sets default values
AShooterEnemy::AShooterEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UShooterCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GAS set up
	AbilitySystemComponent = CreateDefaultSubobject<UMiniShooterAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	//AttributeSet set up
	AttributeSet = CreateDefaultSubobject<UMiniShooterAttributeSet>(TEXT("AttributeEnemyList"));

	//Widget Component
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LifeWidget"));
	HealthBarWidgetComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	
	SuspiciousBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SuspiciousWidget"));
	SuspiciousBarWidgetComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

FVector AShooterEnemy::GetSocketLocation_Implementation()
{
	return Weapon->GetSocketLocation(FName("Muzzle"));
}

FVector AShooterEnemy::GetTargetDirection_Implementation()
{
	return (Cast<AShooterAIController>(Controller)->AIPerceptionComponent->GetActorTarget()->GetActorLocation() - Weapon->GetComponentLocation()).GetSafeNormal();
}

void AShooterEnemy::Die()
{
	SetLifeSpan(2.f); //Harcoded
	Super::Die();
}

// Called when the game starts or when spawned
void AShooterEnemy::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeInitAttributes();
	
	UShooterUserWidget* EnemyLifeBar = Cast<UShooterUserWidget>(HealthBarWidgetComponent->GetUserWidgetObject());
	UShooterUserWidget* EnemySuspiciousBar = Cast<UShooterUserWidget>(SuspiciousBarWidgetComponent->GetUserWidgetObject());

	if (EnemyLifeBar)
	{
		EnemyLifeBar->SetWidgetController(this);
	}

	if(EnemySuspiciousBar)
	{
		EnemySuspiciousBar->SetWidgetController(this);
	}

	UMiniShooterAttributeSet* ATS = Cast<UMiniShooterAttributeSet>(AttributeSet);
	if (ATS)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ATS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
				if (Data.OldValue > Data.NewValue)
				{
					Cast<AShooterAIController>(Controller)->OnGetShot();
				}
			});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ATS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});
		
			OnHealthChanged.Broadcast(ATS->GetHealth());
			OnMaxHealthChanged.Broadcast(ATS->GetMaxHealth());
	}
	
	for (TSubclassOf<UGameplayAbility>& Element : Abilities)
	{
		if (Element)
		{
			AbilitySystemComponent->GiveAbility(Element);
		}
	}
}
