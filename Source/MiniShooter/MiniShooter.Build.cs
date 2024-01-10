// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MiniShooter : ModuleRules
{
	public MiniShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks", "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Slate", "SlateCore", "AIModule" });
	}
}
