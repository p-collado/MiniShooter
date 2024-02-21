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

	//Widget Component
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LifeWidget"));
	WidgetComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

FVector AShooterEnemy::GetSocketLocation_Implementation()
{
	return Weapon->GetSocketLocation(FName("Muzzle"));
}

FVector AShooterEnemy::GetForwardVector_Implementation()
{
	return Weapon->GetForwardVector();
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

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UMiniShooterAttributeSet* ATS = Cast<UMiniShooterAttributeSet>(AttributeSet);
	
	FOnGameplayAttributeValueChange& Delegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMiniShooterAttributeSet::GetHealthAttribute());
	Delegate.AddUObject(this, &AShooterEnemy::OnHealthChanged);

	ApplyEffectToSelf(DefaultEffectAttributes, 1.f);
	
	UEnemyHUD* EnemyHUD = Cast<UEnemyHUD>(WidgetComponent->GetUserWidgetObject());

	if (EnemyHUD)
	{
		EnemyHUD->SetCharacterOwner(this);
		EnemyHUD->BindDelegates();
		EnemyHUD->SetCurrentMaxLife(ATS->GetMaxHealth());
		OnHealthChange.Broadcast(ATS->GetHealth());
	}
	
	for (TSubclassOf<UGameplayAbility>& Element : Abilities)
	{
		if (Element)
		{
			AbilitySystemComponent->GiveAbility(Element);
		}
	}
}

void AShooterEnemy::PostInitializeComponents()
{	
	Super::PostInitializeComponents();
	
}
