// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"

#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "MiniShooter/Character/Components/ShooterCharacterMovement.h"
#include "MiniShooter/GAS/MiniShooterAbilitySystemComponent.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"
#include "MiniShooter/HUD/EnemyHUD.h"

// Sets default values
AShooterEnemy::AShooterEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UShooterCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GAS setup
	AbilitySystemComponent = CreateDefaultSubobject<UMiniShooterAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMiniShooterAttributeSet>(TEXT("AttributeEnemyList"));
	
	//Capsule configuration
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//Widget Component
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LifeWidget"));
	WidgetComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void AShooterEnemy::OnHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	OnHealthChange.Broadcast(OnAttributeChangeData.NewValue);

	if (OnAttributeChangeData.NewValue <= 0)
	{
		Destroy();
	}
}

void AShooterEnemy::BeginDestroy()
{
	Super::BeginDestroy();
	OnHealthChange.Clear();
}

// Called when the game starts or when spawned
void AShooterEnemy::BeginPlay()
{
	Super::BeginPlay();

	UEnemyHUD* casted = Cast<UEnemyHUD>(WidgetComponent->GetUserWidgetObject());
	
	if (casted)
	{
		casted->SetCharacterOwner(this);
	}

	if (AbilitySystemComponent)
	{
		FOnGameplayAttributeValueChange& Delegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMiniShooterAttributeSet::GetHealthAttribute());
		Delegate.AddUObject(this, &AShooterEnemy::OnHealthChanged);
		
		if (InitTable)
		{
			AttributeSet->InitFromMetaDataTable(InitTable);
		}

		for (TSubclassOf<UGameplayAbility>& Element : Abilities)
		{
			if (Element)
			{
				AbilitySystemComponent->GiveAbility(Element);
			}
		}
	}
}

void AShooterEnemy::PostInitializeComponents()
{	
	Super::PostInitializeComponents();
	
}

// Called every frame
void AShooterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

// Called to bind functionality to input
void AShooterEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

