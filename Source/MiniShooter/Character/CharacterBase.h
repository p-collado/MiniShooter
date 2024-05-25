// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "MiniShooter/Interaction/CombatInterface.h"
#include "CharacterBase.generated.h"

//Forward Declarations
class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;
class UDataTable;
class UGameplayEffect;
class USkeletalMeshComponent;

/**
 * @brief Character base class, it has the common features
 */

UCLASS(Abstract)
class MINISHOOTER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ACharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	//Begin Combat Interface
	virtual void Die() override;
	//End Combat Interface

	//Returns Attribute Set
	UAttributeSet* GetAttributeSet() { return AttributeSet; }

	float GetSpeed();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Weapon;

protected:
	
	virtual void BeginPlay() override;

	virtual void InitializeInitAttributes();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const;

	void AddCharacterAbilities();

	UPROPERTY(EditAnywhere, Category= "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= "Attributes")
	TSubclassOf<UGameplayEffect> DefaultEffectAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
};
