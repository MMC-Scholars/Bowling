// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

#include "MMC_Bowling.h"
#include "EngineUtils.h"
#include "info_target.h"


// Sets default values
Ainfo_target::Ainfo_target()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Define our root component as our sprite
	//RootComponent = TargetSprite;
}

//This line is necessary to avoid compiler errors
Ainfo_target * Ainfo_target::originTarget;

//Returns the static target located at the origin
//If it does not already exist, creates it
Ainfo_target * Ainfo_target::GetTargetAtOrigin(UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (!originTarget)
	{
		if (World)
			originTarget = World->SpawnActor<class Ainfo_target>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	return originTarget;
}

//Given a name, finds the target in the world.
Ainfo_target * Ainfo_target::FindTargetByName(const FName targetName, const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	for (TActorIterator<Ainfo_target> ActorItr(World); ActorItr; ++ActorItr)
	{
		Ainfo_target * curTarget = *ActorItr;
		if (curTarget && curTarget->GetFName() == targetName)
			return curTarget;
	}
	return nullptr;
}

Ainfo_target * Ainfo_target::FindTargetNearestToLocation(const FVector worldLocation, const UObject* worldContextObject)
{
	Ainfo_target * nearestTarget = (Ainfo_target*)nullptr;
	if (worldContextObject) {
		//declare local variables
		UWorld* world = GEngine->GetWorldFromContextObject(worldContextObject);
		float minDistance = FLT_MAX;

		//find closest target
		for (TActorIterator<Ainfo_target> ActorItr(world); ActorItr; ++ActorItr) {
			Ainfo_target * curTarget = *ActorItr;

			if (curTarget) {
				float distance = FVector::Dist((curTarget->GetActorLocation() - worldLocation), FVector::ZeroVector);
				if (distance < minDistance) {
					minDistance = distance;
					nearestTarget = curTarget;
				}
			}
		}
	}
	return nearestTarget;
}

//Retrieves the extra information bound to the point. Default is empty string
FString Ainfo_target::GetInfo()
{
	return FString("");
}

//Given an actor, returns the transform from this target to the given actor
FTransform Ainfo_target::GetTransformToActor(AActor *fromActor)
{
	if (fromActor)
	{
		return FTransform(fromActor->GetActorRotation() - this->GetActorRotation(), fromActor->GetActorLocation() - this->GetActorLocation());
	}
	else
		return (FTransform());
}

//Given an actor, returns the vector offset from this target to the given actor
FVector Ainfo_target::GetOffsetToActor(AActor *fromActor)
{
	if (fromActor)
		return (fromActor->GetActorLocation()) - (this->GetActorLocation());
	else
		printWarning("Failed to find get offset to actor");
		return (FVector::ZeroVector);
}




