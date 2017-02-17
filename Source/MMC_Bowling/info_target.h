// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.
/*
Purpose: a simple actor-derived classes which essentially gives a name to a point in the world.
	BP extension has a sprite component.
	Contains static method for finding any info_target, given the name

@author Michael Trunk
*/
#pragma once

#include "GameFramework/Actor.h"
#include "MMC_Shared.h"
#include "util_debug.h"
#include "info_target.generated.h"

UCLASS()
class MMC_BOWLING_API Ainfo_target : public AActor
{
	GENERATED_BODY()
	
public:	
	//Hard-coded sprite component
	/*
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "info_target")
		UPaperSpriteComponent* TargetSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TargetSprite"));
	*/
	// Sets default values for this actor's properties
	Ainfo_target();

	//Static pointer to target at the world origin
	static Ainfo_target *originTarget;

	//Returns the static target located at the origin
	UFUNCTION(BlueprintCallable, Category = "info_target")
		static Ainfo_target *GetTargetAtOrigin(UObject* WorldContextObject);

	//Given a name, finds the target in the world.
	UFUNCTION(BlueprintCallable, Category = "info_target")
		static Ainfo_target *FindTargetByName( UPARAM(ref) FName &targetName, UObject* WorldContextObject);

	//Given an actor, returns the transform from this target to the given actor
	UFUNCTION(BlueprintCallable, Category = "info_target")
		FTransform GetTransformToActor(AActor *fromActor);

	//Given an actor, returns the vector offset from this target to the given actor
	UFUNCTION(BlueprintCallable, Category = "info_target")
		FVector GetOffsetToActor(AActor *fromActor);
	
	
};
