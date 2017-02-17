// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

/*
Purpose: This class contains common macro definitions that are utilized across  
*/

#pragma once

//Aliases for printing debug messages to screen
#define printBlurp(a) Autil_debug::PrintBlurp(a)
#define printMessage(a) Autil_debug::PrintMessage(a)
#define printWarning(a) Autil_debug::PrintWarning(a)
#define printFatal(a) Autil_debug::PrintFatal(a)


//this is used by all the gset functions
#define OVERRIDE_TYPE_SET		0
#define OVERRIDE_TYPE_ADD		1
#define OVERRIDE_TYPE_SUBTRACT	2
#define OVERRIDE_TYPE_MULTIPLY	3
#define OVERRIDE_TYPE_NULL		4

//Don't actually use this decleration macro because UnrealHeaderTool won't like it
#if 0
#define DECLARE_FINDER(className, commonName) \
	static className *Find##commonName##ByName(FName targetName, UObject const * const WorldContextObject);
#endif

//Use this as an alias for implementing finder functions for actors. This finder function 
//must have a definition in the class definition matching that declared in the macro above this one
#define IMPLEMENT_FINDER(className, commonName) \
	className * className##::Find##commonName##ByName(FName targetName, UObject const * const WorldContextObject) \
	{\
		if (WorldContextObject)\
		{\
			UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);\
			for (TActorIterator<##className##> ActorItr(World); ActorItr; ++ActorItr)\
			{\
				className * cur##commonName = *ActorItr;\
				if (cur##commonName && cur##commonName##->GetFName() == targetName)\
					return cur##commonName##;\
			}\
			printWarning(FString("Failed to fine actor ") + targetName.ToString());\
		}\
		return nullptr;\
	}