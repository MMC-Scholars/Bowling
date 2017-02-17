// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs
/*
Purpose: a base filter class which models a filter: An actor or 
		array of actors comes in, fewer come out.
	The terms by which actors do or do not pass can be specified.
	Also contains static functions for finding and using filters.

@author Michael Trunk
*/

#pragma once

#include "GameFramework/Actor.h"
#include <entity_base.h>
#include "MMC_Shared.h"
#include "filter_base.generated.h"

//An estimation of what proportion of a filtered array will pass.
//This is used to reserve space for creating new output arrays based
//on the size of the given array. Larger amounts will take up more memory,
//smaller amounts will reduce performance
#define ARRAY_SIZE_CHANGE_ESTIMATE 0.5f


UENUM(BlueprintType)
enum FilterType
{
	ByClass					UMETA(DisplayName = "ByClass"),
	ByName					UMETA(DisplayName = "ByName"),
	ByTag					UMETA(DisplayName = "ByTag"),
	ByIsVisible				UMETA(DisplayName = "ByIsVisible"),
	ByIsSolid				UMETA(DisplayName = "ByIsSolid"),
	ByIsPhysicsSimulated	UMETA(DisplayName = "ByIsPhysicsSimulated")
};

UENUM(BlueprintType)
enum FilterMode
{
	Normal				UMETA(DisplayName = "Normal"),
	Inverted			UMETA(DisplayName = "Inverted"),
	Random				UMETA(DisplayName = "Random"),
};

UCLASS()
class MMC_BOWLING_API Afilter_base : public AActor
{
	GENERATED_BODY()
	
private:	
	// Private constructor so this class can't be instantiated
	Afilter_base();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	STATIC FUNCTIONS
	*/
	//Given an array of actors and the name of a filter, returns the filtered array of actors
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		static TArray<AActor*> FilterActorArrayByFilterName(const TArray<AActor*> & filterMe, const FName filterName);

	//Randomly filters an array of actors using the specified filter's random filter
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		static TArray<AActor*> FilterActorArrayRandomlyByFilterName(const TArray<AActor*> & filterMe, const FName filterName);
	
	//Given an actor and the name of a filter, returns true if the actor passes the filter, false otherwise
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		static bool FilterActorByFilterName(AActor const * const filterMe, const FName filterName);

	//Given an actor and the name of a filter, returns true if the actor passes the filter, false otherwise
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		static bool FilterActorRandomlyByFilterName(AActor const * const filterMe, const FName filterName);

	//Declare macro'ed finder function
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		static Afilter_base *FindFilterByName(FName targetName, UObject const * const WorldContextObject);

	/*
	MEMBER VARIABLES
	*/
	//How to treat actors who meet conditions. Normal is pass, inverted is fail, random is random. Random will override filterType
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "filter_base")
		TEnumAsByte<FilterMode> mode = Normal;

	//How to filter through actors
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "filter_base")
		TEnumAsByte<FilterType> filterType = ByClass;

	//If filterType == ByClass, tested actors must be of this class to pass
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "filter_base")
		UClass* filterByClassParemeter;

	//If filterType is ByName or ByTag, this is used to to test actors
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "filter_base")
		FName filterByTextParameter;

	//If specified, actors will also have to pass this other filter in order to pass this filter
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "filter_base")
		FName subFilterName;

	//Proportion of tests that pass. 0 is none, 1 is all
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "filter_base", meta = (UIMin = "0.0", UIMax = "1.0"))
		float randomFilterBias = 0.5f;

	//Whether or not to generate pass/fail events
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "filter_base")
		bool bGeneratePassFailEvents = true;

	/*
	MEMBER FUNCTIONS
	*/
	//Filters an array through this filter
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		TArray<AActor*> FilterActorArray(const TArray<AActor*> & filterMe) const;

	//Randomly filters an array through this filter
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		TArray<AActor*> FilterActorArrayRandomly(const TArray<AActor*> & filterMe) const;

	//Checks if an actor would pass this filter
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		bool FilterActor(AActor const * const filterMe) const;

	//Checks if an actor would pass this filter randomly
	UFUNCTION(BlueprintCallable, Category = "filter_base")
		bool FilterActorRandomly(AActor const * const filterMe) const;

protected:
	//For getting pointer to the sub-filter
	FORCEINLINE Afilter_base * GetSubFilter() const { return dynamic_cast<Afilter_base*>(Aentity_base::FindActorByName(subFilterName, this)); };

public:
	/*
	IMPLEMENTABLE BP EVENTS
	*/
	//Called whenever an actor or actor-array-element passes this filter
	UFUNCTION(BlueprintImplementableEvent, Category = "filter_base")
		void OnPass(AActor const * const passedActor) const;

	UFUNCTION(BlueprintImplementableEvent, Category = "filter_base")
		void OnFail(AActor const * const failedActor) const;


	





	
	
};
