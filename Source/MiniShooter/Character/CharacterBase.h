// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "MiniShooter/Interaction/CombatInterface.h"
#include "CharacterBase.generated.h"

class UGameplayAbility;
//Forward Declarations
class UAttributeSet;
class UAbilitySystemComponent;
class UDataTable;
class UGameplayEffect;

class USkeletalMeshComponent;

UCLASS(Abstract)
class MINISHOOTER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ACharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	//Returns Attribute Set
	UAttributeSet* GetAttributeSet() { return AttributeSet; }

	float GetSpeed();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Weapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
