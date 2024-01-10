// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "ShooterEnemy.generated.h"

//Forward Declarations
class UAIPerceptionComponent;
class UWidgetComponent;
class UMiniShooterAttributeSet;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyHealthChange,const float, CharacterHealth);

UCLASS()
class MINISHOOTER_API AShooterEnemy : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterEnemy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

protected:

	//Health Handle Delegate
	void OnHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData);

	virtual void BeginDestroy() override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called after having the components initialized
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when it is possessed
	virtual void PossessedBy(AController* NewController) override;

	//Returns Attribute Set
	const UMiniShooterAttributeSet* GetAttributeSet() { return AttributeSet; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category= "HUD")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	UMiniShooterAttributeSet* AttributeSet;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FEnemyHealthChange OnHealthChange;

	UPROPERTY(EditAnywhere, Category="GAS")
	UDataTable* InitTable;

	UPROPERTY(EditAnywhere, Category="GAS")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	
};
