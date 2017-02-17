// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.
/*
Purpose: non-instantiable utility class which contains helper debuging functions.
	Contains functions for printing out different kinds of messages to the screen.

@author Michael Trunk
*/

#pragma once

#include "GameFramework/Actor.h"
#include "util_debug.generated.h"

UCLASS()
class MMC_BOWLING_API Autil_debug : public AActor
{
	GENERATED_BODY()
	
private:
	// Private constructor so that this class can never be instantiated
	Autil_debug();


	//Static const colors - there are given values in the cpp
	static const FColor BLURP_COLOR;
	static const FColor MESSAGE_COLOR;
	static const FColor WARNING_COLOR;
	static const FColor FATAL_COLOR;

public:
	//Hidden helper function for actually printing a message on the screen
	static void PrintMessage(FString message, float timeToDisplay, FColor color);

	//Prints a message for a very short amount of time - ideal for frame-by-frame
	UFUNCTION(BlueprintCallable, Category = "Debug")
		static void PrintBlurp(FString message);

	//Prints a generic message to the screen
	UFUNCTION(BlueprintCallable, Category = "Debug")
		static void PrintMessage(FString message);
	
	//Prints a warning to the screen
	UFUNCTION(BlueprintCallable, Category = "Debug")
		static void PrintWarning(FString message);

	//Prints a eye-catching long-lasting red error message to the screen
	UFUNCTION(BlueprintCallable, Category = "Debug")
		static void PrintFatal(FString message);


};

