// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Bowling.h"
#include "util_debug.h"

//Set values of the message colors

const FColor Autil_debug::BLURP_COLOR = FColor::Blue;
const FColor Autil_debug::MESSAGE_COLOR = BLURP_COLOR;
const FColor Autil_debug::WARNING_COLOR = FColor::Yellow;
const FColor Autil_debug::FATAL_COLOR = FColor::Blue;

// Private Constructor prevents instantiation
Autil_debug::Autil_debug()
{
	PrimaryActorTick.bCanEverTick = false;
}

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



