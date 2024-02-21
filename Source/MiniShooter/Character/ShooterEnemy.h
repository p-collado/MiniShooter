// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "MiniShooter/Character/CharacterBase.h"
#include "ShooterEnemy.generated.h"

//Forward Declarations
class APatrolPath;
class UAIPerceptionComponent;
class UWidgetComponent;
class UMiniShooterAttributeSet;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyHealthChange,const float, CharacterHealth);

UCLASS()
class MINISHOOTER_API AShooterEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//Begin Combat Interface
	virtual FVector GetSocketLocation_Implementation() override;
	virtual FVector GetForwardVector_Implementation() override;
	//End Combat Interface

protected:

	//Health Handle Delegate
	void OnHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData);

	virtual void BeginDestroy() override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called after having the components initialized
	virtual void PostInitializeComponents() override;

public:
	
	UPROPERTY(EditAnywhere, Category= "HUD")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FEnemyHealthChange OnHealthChange;

	UPROPERTY(EditAnywhere, Category="GAS")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	APatrolPath* PatrolPath;
	
};
