// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheHollowTomb : ModuleRules
{
	public TheHollowTomb(ReadOnlyTargetRules Target) : base(Target)
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
			"TheHollowTomb",
			"TheHollowTomb/Variant_Platforming",
			"TheHollowTomb/Variant_Platforming/Animation",
			"TheHollowTomb/Variant_Combat",
			"TheHollowTomb/Variant_Combat/AI",
			"TheHollowTomb/Variant_Combat/Animation",
			"TheHollowTomb/Variant_Combat/Gameplay",
			"TheHollowTomb/Variant_Combat/Interfaces",
			"TheHollowTomb/Variant_Combat/UI",
			"TheHollowTomb/Variant_SideScrolling",
			"TheHollowTomb/Variant_SideScrolling/AI",
			"TheHollowTomb/Variant_SideScrolling/Gameplay",
			"TheHollowTomb/Variant_SideScrolling/Interfaces",
			"TheHollowTomb/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
