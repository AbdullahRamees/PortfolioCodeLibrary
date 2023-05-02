// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_07 : ModuleRules
{
	public Project_07(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayTasks", "UMG" });
	}
}
