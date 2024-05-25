// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "MiniShooter/UI/Controllers/OverlayWidgetController.h"
#include "MiniShooter/Character/CharacterBase.h"
#include "ShooterEnemy.generated.h"

//Forward Declarations
class APatrolPath;
class UAIPerceptionComponent;
class UWidgetComponent;
class UMiniShooterAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class MINISHOOTER_API AShooterEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	//Begin Combat Interface
	virtual FVector GetSocketLocation_Implementation() override;
	virtual FVector GetTargetDirection_Implementation() override;
	virtual void Die() override;
	//End Combat Interface

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere, Category= "HUD")
	UWidgetComponent* HealthBarWidgetComponent;

	UPROPERTY(EditAnywhere, Category= "HUD")
	UWidgetComponent* SuspiciousBarWidgetComponent;

	UPROPERTY(EditAnywhere, Category="GAS")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	APatrolPath* PatrolPath;
	
};
