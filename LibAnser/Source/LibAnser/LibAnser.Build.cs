// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LibAnser : ModuleRules
{
	public LibAnser(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"LibAnser/Public"
				// ... add public include paths required here ...
               
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"LibAnser/Private"
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
//                     "CoreUObject",
//                     "Engine",
//                     "InputDevice",
//                     "InputCore",
//                     "Sockets",
//                     "Networking",
//                     "HeadMountedDisplay",
//                     "ProceduralMeshComponent",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
