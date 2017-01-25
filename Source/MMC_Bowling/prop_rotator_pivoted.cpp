// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Bowling.h"
#include "prop_rotator_pivoted.h"

void Aprop_rotator_pivoted::BeginPlay() 
{
	Super::BeginPlay();

	SetTargetByName(targetName);
}

Ainfo_target * Aprop_rotator_pivoted::GetTarget()
{
	return target;
}

void Aprop_rotator_pivoted::SetTarget(Ainfo_target * newTarget)
{
	//Don't set it unless the new pointer is good
	if (newTarget)
		target = newTarget;

	if (target)
	{
		locationFromTarget = target->GetOffsetToActor(this);
		transformFromTarget = target->GetTransformToActor(this);
	}
}

void Aprop_rotator_pivoted::SetTargetByName(FName &newTargetName)
{
	SetTarget(Ainfo_target::FindTargetByName(newTargetName, this));
}

void Aprop_rotator_pivoted::SetPosition(float lerp)
{
	//TODO Implement
	//Super::SetPosition(lerp);
}
