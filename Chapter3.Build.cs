// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Chapter3 : ModuleRules
{
	public Chapter3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
