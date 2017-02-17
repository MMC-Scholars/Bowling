// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

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
