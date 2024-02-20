#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FShooterGameplayTags
{
	static const FShooterGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	/*
	 *	Vital Tags
	 */

	FGameplayTag Attributes_Vital_MaxHealth;

	/*
	 * Combat Tags
	 */

	FGameplayTag Attributes_Combat_Ammo;
	FGameplayTag Attributes_Combat_FireRate;
	FGameplayTag Attributes_Combat_Armor;
	FGameplayTag Damage;

	/*
	 * Input Tags
	 */

	FGameplayTag Input_LMB;
	FGameplayTag Input_RMB;
	FGameplayTag Input_SpaceBar;
	FGameplayTag Input_Tab;
	FGameplayTag Input_E;
	FGameplayTag Input_R;
	FGameplayTag Input_P;
	FGameplayTag Input_LeftCtrl;

	/*
	 * CooldownTags
	 */

	FGameplayTag Cooldown_Shoot;

private:

	static FShooterGameplayTags GameplayTags;
};
