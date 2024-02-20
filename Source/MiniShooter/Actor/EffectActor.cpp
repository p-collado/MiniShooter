// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values
AEffectActor::AEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass,
	bool bIsInfinite, EEffectRemovalPolicy RemovalPolicy)
{

	UAbilitySystemComponent* ASCTarget = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = ASCTarget->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = ASCTarget->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = ASCTarget->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	if (bIsInfinite && RemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle, ASCTarget);
		return;
	}

	const bool IsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (IsInfinite && RemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle, ASCTarget);
	}
}

void AEffectActor::OnOverlap(AActor* TargetActor)
{
	for (const FEffectAndPolicyData& Element : InstantGameplayEffectClasses)
	{
		if (Element.GameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, Element.GameplayEffectClass);
		}
	}
	for (const FEffectAndPolicyData& Element : DurationGameplayEffectClasses)
	{
		if (Element.GameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, Element.GameplayEffectClass);
		}
	}
	for (const FEffectAndPolicyData& Element : InfiniteGameplayEffectClasses)
	{
		if(Element.GameplayEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, Element.GameplayEffectClass, Element.bIsInfinite);
		}
	}
}

void AEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for (const FEffectAndPolicyData& Element : InstantGameplayEffectClasses)
	{
		if (Element.GameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, Element.GameplayEffectClass);
		}
	}
	for (const FEffectAndPolicyData& Element : DurationGameplayEffectClasses)
	{
		if (Element.GameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, Element.GameplayEffectClass);
		}
	}

	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	for (const FEffectAndPolicyData& Element : InfiniteGameplayEffectClasses)
	{
		if(Element.GameplayEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, Element.GameplayEffectClass, Element.bIsInfinite);
		}
		
		if (Element.InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
			if (!IsValid(TargetASC))
			{
				continue;
			}
			
			for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
			{
				if (TargetASC == HandlePair.Value)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
					HandlesToRemove.Add(HandlePair.Key);
				}
			}
		}
	}
	
	for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
	{
		ActiveEffectHandles.FindAndRemoveChecked(Handle);
	}
}
