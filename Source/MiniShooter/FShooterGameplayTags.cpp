#include "FShooterGameplayTags.h"
#include "GameplayTagsManager.h"

FShooterGameplayTags FShooterGameplayTags::GameplayTags;

void FShooterGameplayTags::InitializeNativeGameplayTags()
{
	//Secondary
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"), FString("Max Health Tag"));

	//Combat
	GameplayTags.Attributes_Combat_Ammo = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Combat.Ammo"), FString("Ammo Tag"));
	GameplayTags.Attributes_Combat_FireRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Combat.FireRate"), FString("FireRate Tag"));
	GameplayTags.Attributes_Combat_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Combat.Armor"), FString("Armor tag"));
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage tag"));

	//Input
	GameplayTags.Input_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LMB"), FString("LMB input tag"));
	GameplayTags.Input_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.RMB"), FString("RMB input tag"));
	GameplayTags.Input_SpaceBar = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.SpaceBar"), FString("Space bar input tag"));
	GameplayTags.Input_Tab = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Tab"), FString("Tab input tag"));
	GameplayTags.Input_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.E"), FString("E input tag"));
	GameplayTags.Input_R = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.R"), FString("R input tag"));
	GameplayTags.Input_P = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.P"), FString("P input tag"));
	GameplayTags.Input_LeftCtrl = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LeftCtrl"), FString("LeftCtrl input tag"));

	//Cooldown
	GameplayTags.Cooldown_Shoot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Shoot"), FString("Cooldown Shoot tag"));
}
