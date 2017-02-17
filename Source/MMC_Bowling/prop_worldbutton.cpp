// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

#include "MMC_Bowling.h"
#include "prop_worldbutton.h"

//Constructor
Aprop_worldbutton::Aprop_worldbutton()
{
	//Make sure this happens
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aprop_worldbutton::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void Aprop_worldbutton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


//Presses the button if it is available to be pressed
void Aprop_worldbutton::Press()
{
	if (bIsLocked)
		OnUseLocked();
	else
	{
		OnPressed();
		if (!bDontMoveOnPress)
			Open();
	}
		
}

//overrides for opening, to check if we even can move the button
bool Aprop_worldbutton::Use(AActor * caller)
{
	if (bIgnoreUse)
	{
		OnUseIgnored(caller);
		return false;
	}
	Press();

	OnUse(caller);
	return true;
}

