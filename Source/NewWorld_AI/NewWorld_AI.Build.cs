// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NewWorld_AI : ModuleRules
{
	public NewWorld_AI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = true;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks", "GameplayTags" });
	}
}
