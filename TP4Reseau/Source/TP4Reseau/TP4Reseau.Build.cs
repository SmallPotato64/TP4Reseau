// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP4Reseau : ModuleRules
{
	public TP4Reseau(ReadOnlyTargetRules Target) : base(Target)
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
			"TP4Reseau",
			"TP4Reseau/Variant_Platforming",
			"TP4Reseau/Variant_Platforming/Animation",
			"TP4Reseau/Variant_Combat",
			"TP4Reseau/Variant_Combat/AI",
			"TP4Reseau/Variant_Combat/Animation",
			"TP4Reseau/Variant_Combat/Gameplay",
			"TP4Reseau/Variant_Combat/Interfaces",
			"TP4Reseau/Variant_Combat/UI",
			"TP4Reseau/Variant_SideScrolling",
			"TP4Reseau/Variant_SideScrolling/AI",
			"TP4Reseau/Variant_SideScrolling/Gameplay",
			"TP4Reseau/Variant_SideScrolling/Interfaces",
			"TP4Reseau/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
