// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MovementResearch : ModuleRules
{
	public MovementResearch(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MovementResearch",
			"MovementResearch/Variant_Platforming",
			"MovementResearch/Variant_Platforming/Animation",
			"MovementResearch/Variant_Combat",
			"MovementResearch/Variant_Combat/AI",
			"MovementResearch/Variant_Combat/Animation",
			"MovementResearch/Variant_Combat/Gameplay",
			"MovementResearch/Variant_Combat/Interfaces",
			"MovementResearch/Variant_Combat/UI",
			"MovementResearch/Variant_SideScrolling",
			"MovementResearch/Variant_SideScrolling/AI",
			"MovementResearch/Variant_SideScrolling/Gameplay",
			"MovementResearch/Variant_SideScrolling/Interfaces",
			"MovementResearch/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
