// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MMC_BowlingEditorTarget : TargetRules
{
	public MMC_BowlingEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
	
		ExtraModuleNames.Add("MMC_Bowling");

	}


}
