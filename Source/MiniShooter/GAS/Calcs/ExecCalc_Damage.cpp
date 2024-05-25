// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecCalc_Damage.h"

#include "MiniShooter/FShooterGameplayTags.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

struct ShooterDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	ShooterDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMiniShooterAttributeSet, Armor, Target, false);

		const FShooterGameplayTags& Tags = FShooterGameplayTags::Get();
		
		TagsToCaptureDefs.Add(Tags.Attributes_Combat_Armor, ArmorDef);
	}
};

static const ShooterDamageStatics& DamageStatics()
{
	static ShooterDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC =  ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC =  ExecutionParams.GetTargetAbilitySystemComponent();
	
	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	//Cogemos los tags que tengan en ese momento el target y el source
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//Esto lo necesitamos para intentar calcular la magnitud de un atributo
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.f;
	const FGameplayEffectAttributeCaptureDefinition CaptureDef = ShooterDamageStatics().TagsToCaptureDefs[FShooterGameplayTags::Get().Attributes_Combat_Armor];
	float DamageTypeValue = Spec.GetSetByCallerMagnitude(FShooterGameplayTags::Get().Damage, false);
	
	float Resistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
	Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

	//Aqui poner la formula del daño que diseño se ponga creativo, en este caso pongo una de effectividad.
	DamageTypeValue *= ( 100.f - Resistance ) / 100.f;
	Damage += DamageTypeValue;

	const FGameplayModifierEvaluatedData EvaluatedData(UMiniShooterAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}


