// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "EffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum EEffectApplicationPolicy
{
	ApplyOnOverlap
   ,ApplyOnEndOverlap
   ,DoNotApply
};

UENUM(BlueprintType)
enum EEffectRemovalPolicy
{
	RemoveOnEndOverlap
   ,DoNotRemove
};


USTRUCT(BlueprintType)
struct FEffectAndPolicyData
{
	GENERATED_BODY()

	FEffectAndPolicyData(){};

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	bool bIsInfinite = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	TEnumAsByte<EEffectApplicationPolicy> GameplayEffectApplicationPolicy = DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	TEnumAsByte<EEffectRemovalPolicy> InfiniteEffectRemovalPolicy = DoNotRemove;
};

UCLASS()
class MINISHOOTER_API AEffectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable, meta=(HidePin = "bIsInfinite"))
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass, bool bIsInfinite = false, EEffectRemovalPolicy RemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	TArray<FEffectAndPolicyData> InstantGameplayEffectClasses;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	TArray<FEffectAndPolicyData> DurationGameplayEffectClasses;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	TArray<FEffectAndPolicyData> InfiniteGameplayEffectClasses;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Effects")
	float ActorLevel = 1.f;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
};
