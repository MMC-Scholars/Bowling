// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.


#include "MMC_Bowling.h"
#include "util_debug.h"

// Private Constructor prevents instantiation
Autil_debug::Autil_debug()
{
	PrimaryActorTick.bCanEverTick = false;
}

//Set values of the message colors
const FColor Autil_debug::BLURP_COLOR = FColor::Cyan;
const FColor Autil_debug::MESSAGE_COLOR = BLURP_COLOR;
const FColor Autil_debug::WARNING_COLOR = FColor::Yellow;
const FColor Autil_debug::FATAL_COLOR = FColor::Blue;

//Hidden helper function for actually printing a message on the screen
void Autil_debug::PrintMessage(FString message, float timeToDisplay, FColor color)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, timeToDisplay, color, message);
}

//Prints a message for a very short amount of time - ideal for frame-by-frame
void Autil_debug::PrintBlurp(FString message)
{
	PrintMessage(message, 0.0167f, BLURP_COLOR);
}

//Prints a generic message to the screen
void Autil_debug::PrintMessage(FString message)
{
	PrintMessage(message, 5.0f, MESSAGE_COLOR);
}

//Prints a warning to the screen
void Autil_debug::PrintWarning(FString message)
{
	PrintMessage(message, 15.0f, WARNING_COLOR);
}

//Prints a eye-catching long-lasting red error message to the screen
void Autil_debug::PrintFatal(FString message)
{
	PrintMessage(message, 60.0f, FATAL_COLOR);
}



