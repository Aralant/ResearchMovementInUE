// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ResearchMovementInUE : ModuleRules
{
	public ResearchMovementInUE(ReadOnlyTargetRules Target) : base(Target)
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
			"ResearchMovementInUE",
			"ResearchMovementInUE/Variant_Platforming",
			"ResearchMovementInUE/Variant_Platforming/Animation",
			"ResearchMovementInUE/Variant_Combat",
			"ResearchMovementInUE/Variant_Combat/AI",
			"ResearchMovementInUE/Variant_Combat/Animation",
			"ResearchMovementInUE/Variant_Combat/Gameplay",
			"ResearchMovementInUE/Variant_Combat/Interfaces",
			"ResearchMovementInUE/Variant_Combat/UI",
			"ResearchMovementInUE/Variant_SideScrolling",
			"ResearchMovementInUE/Variant_SideScrolling/AI",
			"ResearchMovementInUE/Variant_SideScrolling/Gameplay",
			"ResearchMovementInUE/Variant_SideScrolling/Interfaces",
			"ResearchMovementInUE/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
