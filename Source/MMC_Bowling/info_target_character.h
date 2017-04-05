// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

/*
A simple extension of the info_target class which allows for storing an extra
FString of information which is bound to the point in question

@author Michael Trunk
*/
#pragma once

#include "info_target.h"
#include "info_target_character.generated.h"



UCLASS()
class MMC_BOWLING_API Ainfo_target_character : public Ainfo_target
{
	GENERATED_BODY()

public:
	Ainfo_target_character();

	//For attaching extra information to the point in the world
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "info_target_character")
	FString info;
	
	UFUNCTION(BlueprintCallable, Category = "info_target")
		virtual FString GetInfo() override;

	//Finds the nearest info_target and if it's an info_target_characters appends its info to the given string
	UFUNCTION(BlueprintCallable, Category = "info_target_character")
		static void AppendNearestCharacterTarget(FVector worldLocation, UPARAM(ref) FString& appendedString, const UObject * worldContextObject);
	
	
};
