// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Bowling.h"
#include "filter_base.h"


// Sets default values
Afilter_base::Afilter_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void Afilter_base::BeginPlay()
{
	Super::BeginPlay();
	
}

//Given an array of actors and the name of a filter, returns the filtered array of actors
TArray<AActor*> Afilter_base::FilterActorArrayByFilterName(const TArray<AActor*> & filterMe, const FName filterName)
{
	//Get a world context object from one of the actors
	UObject * contextObject = nullptr;
	int i = 0;  while (!contextObject && i < filterMe.Num())
	{
		contextObject = filterMe[i];
		i++;
	}
	if (contextObject)
	{
		Afilter_base * filter = dynamic_cast<Afilter_base*>(Aentity_base::FindActorByName(filterName, contextObject));

		if (filter)
			return filter->FilterActorArray(filterMe);
	}

	//if all else fails then just return an empty array
	TArray<AActor*> empty = TArray<AActor*>();
	return empty;
}

//Randomly filters an array of actors using the specified filter's random filter
TArray<AActor*> Afilter_base::FilterActorArrayRandomlyByFilterName(const TArray<AActor*>& filterMe, const FName filterName)
{
	//Get a world context object from one of the actors
	UObject * contextObject = nullptr;
	int i = 0;  
	while (!contextObject && i < filterMe.Num())
	{
		contextObject = filterMe[i];
		i++;
	}
	if (contextObject)
	{
		Afilter_base * filter = dynamic_cast<Afilter_base*>(Aentity_base::FindActorByName(filterName, contextObject));

		if (filter)
			return filter->FilterActorArrayRandomly(filterMe);
	}
	
	
	//if all else fails then just return an empty array
	TArray<AActor*> empty = TArray<AActor*>();
	return empty;
}

//Given an actor and the name of a filter, returns true if the actor passes the filter, false otherwise.
bool Afilter_base::FilterActorByFilterName(AActor const * const filterMe, const FName filterName)
{
	Afilter_base * filter = dynamic_cast<Afilter_base*>(Aentity_base::FindActorByName(filterName, filterMe));

	if (filter)
		return filter->FilterActor(filterMe);

	//return false by default
	return false;
}

bool Afilter_base::FilterActorRandomlyByFilterName(AActor const * const filterMe, const FName filterName)
{
	Afilter_base * filter = dynamic_cast<Afilter_base*>(Aentity_base::FindActorByName(filterName, filterMe));

	if (filter)
		return filter->FilterActorRandomly(filterMe);

	//return false by default
	return false;
}

//Filters an array through this filter
TArray<AActor*> Afilter_base::FilterActorArray(const TArray<AActor*>& filterMe) const
{
	//Create a new array and reserve space for it
	TArray<AActor*> newArray = TArray<AActor*>();
	newArray.Reserve(static_cast<int>(filterMe.Num() * ARRAY_SIZE_CHANGE_ESTIMATE));

	for (int i = 0; i < filterMe.Num(); i++)
	{
		if (filterMe[i] && FilterActor(filterMe[i])) {
			newArray.AddUnique(filterMe[i]);
		}	
	}
	return newArray;
}

TArray<AActor*> Afilter_base::FilterActorArrayRandomly(const TArray<AActor*>& filterMe) const
{
	//Create a new array and reserve space for it
	TArray<AActor*> newArray = TArray<AActor*>();
	newArray.Reserve(static_cast<int>(filterMe.Num() * ARRAY_SIZE_CHANGE_ESTIMATE));

	for (int i = 0; i < filterMe.Num(); i++)
	{
		if (filterMe[i] && FilterActorRandomly(filterMe[i])) {
			newArray.AddUnique(filterMe[i]);
		}
	}
	return newArray;
}

//Checks if an actor would pass this filter
bool Afilter_base::FilterActor(AActor const * const filterMe) const
{
	//First check that the pointer is good
	if (!filterMe)
		return false;

	//Then check if we're supposed to be random by default
	if (mode == Random)
		return FilterActorRandomly(filterMe);

	bool bPassed = false;

	//Now actually check the actor against the filter parameters
	switch (filterType)
	{
		case (ByClass):
			bPassed = (filterByClassParemeter && filterByClassParemeter == filterMe->GetClass());
			break;
		case (ByName):
			bPassed = (filterByTextParameter.ToString() == filterMe->GetName());
			break;
		case (ByTag):
			bPassed = (filterMe->ActorHasTag(filterByTextParameter));
			break;
		case (ByIsVisible):
			bPassed = (filterMe->GetRootComponent() && filterMe->GetRootComponent()->IsVisible());
			break;
		case (ByIsSolid):
			bPassed = (filterMe->GetRootComponent() && filterMe->GetRootComponent()->IsPhysicsCollisionEnabled());
			break;
		case (ByIsPhysicsSimulated):
			bPassed = (filterMe->GetRootComponent() && filterMe->GetRootComponent()->IsSimulatingPhysics());
			break;
	}

	if (bGeneratePassFailEvents)
	{
		if (bPassed)
			OnPass(filterMe);
		else
			OnFail(filterMe);
	}
	//Check if we invert the result
	bPassed = (mode == Inverted) ? !bPassed : bPassed;

	//Finally, pass it to the subfilter if it exists
	Afilter_base * subFilter = GetSubFilter();
	if (bPassed && subFilter && subFilter->GetSubFilter() != this)
	{
		bPassed = subFilter->FilterActor(filterMe);
	}

	return bPassed;
}

bool Afilter_base::FilterActorRandomly(AActor const * const filterMe) const
{
	//First check that the pointer is good
	if (!filterMe)
		return false;
	
	bool bPassed = (FMath::RandRange(0, 1) < randomFilterBias);

	//Check if we invert the result
	if (mode == Inverted) bPassed = !bPassed;

	//Finally, pass it to the subfilter if it exists
	Afilter_base * subFilter = GetSubFilter();
	if (bPassed && subFilter && subFilter->GetSubFilter() != this)
	{
		bPassed = subFilter->FilterActor(filterMe);
	}

	if (bGeneratePassFailEvents)
	{
		if (bPassed)
			OnPass(filterMe);
		else
			OnFail(filterMe);
	}

	return bPassed;
}