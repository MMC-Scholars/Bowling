// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

#include "MMC_Bowling.h"
#include "info_target_character.h"

Ainfo_target_character::Ainfo_target_character()
{
	info = FString("");
}

FString Ainfo_target_character::GetInfo()
{
	return this->info;
}

void Ainfo_target_character::AppendNearestCharacterTarget(FVector worldLocation, FString& appendedString, const UObject * worldContextObject)
{
	if (worldContextObject) {
		Ainfo_target_character * nearestTarget = dynamic_cast<Ainfo_target_character*>(FindTargetNearestToLocation(worldLocation, worldContextObject));
		if (nearestTarget) {
			appendedString += nearestTarget->GetInfo();
		}
	}
}

