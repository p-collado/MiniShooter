// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

//Forward Declarations
class UAttributeSet;
class UAbilitySystemComponent;
class UDataTable;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FCombatUtils
{
	GENERATED_BODY()

	FCombatUtils(){};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector ShootPosition;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector ShootDirection;
	
};

class USkeletalMeshComponent;

UCLASS(Abstract)
class MINISHOOTER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCombatUtils CombatUtils;

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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= "Attributes")
	TSubclassOf<UGameplayEffect> DefaultEffectAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="GAS")
	UDataTable* InitTable;
	
};
