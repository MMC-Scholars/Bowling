// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

#include "MMC_Bowling.h"
#include "prop_move_base.h"

void Aprop_move_base::SetSpeed(float newSpeed)
{
	//Implemented by children classes
}

Aprop_move_base::Aprop_move_base()
{
	PrimaryActorTick.bCanEverTick = true;
}

void Aprop_move_base::BeginPlay()
{
	Super::BeginPlay();


	//Call SetSpeed(...) to calculate the initial lerp speed or whatever else is defined
	SetSpeed(movementSpeed);
}

void Aprop_move_base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//These subroutines are implemented by children classes
	if (bIsOpening)
		processOpen(DeltaSeconds);
	else if (bIsClosing)
		processClose(DeltaSeconds);
	else if (bIsWaitingToClose)
		processWaitedClose(DeltaSeconds);
}

/*
These next two functions and defined by child classes
*/
void Aprop_move_base::processOpen(float DeltaSeconds)
{
}

void Aprop_move_base::processClose(float DeltaSeconds)
{
}




void Aprop_move_base::processWaitedClose(float DeltaSeconds)
{
	waitingTime += DeltaSeconds;
	if (waitingTime >= delayBeforeReset)
		Close();
}

void Aprop_move_base::Open()
{
	//First check if the door is locked
	if (bIsLocked)
	{
		OnUseLocked();
		return;
	}
	//Don't do anything if we're already opening
	if (bIsOpening)
		return;

	//Call the implementable event
	OnOpened();

	//make sure we stop closing and start opening; also start waiting
	bIsClosing = false;
	bIsOpening = true;

	//only start waiting if the time to close again is greater than 0
	if (delayBeforeReset > 0.0f)
		bIsWaitingToClose = true; waitingTime = 0.0f;
	//the tick function will then call for processOpen(...)
}

void Aprop_move_base::Close()
{
	//First check if the door is locked
	if (bIsLocked)
	{
		OnUseLocked();
		return;
	}
	//Don't do anything if we're already closing
	if (bIsClosing)
		return;

	//Call the implementable event
	OnClosed();

	//make sure we stop opening and start closing; also stop waiting
	bIsClosing = true;
	bIsOpening = false;
	bIsWaitingToClose = false; waitingTime = 0.0f;
	//the tick function will then call for processClose(...)
}

void Aprop_move_base::Toggle()
{
	//First check if the door is locked
	if (bIsLocked)
	{
		OnUseLocked();
		return;
	}
	if (IsOpen() || bIsOpening)
		Close();
	else
		Open(); //this defaults the door to opening when in a paused state
}

//Override for entity_base use - calls for toggling the door
bool Aprop_move_base::Use(AActor * caller)
{
	if (bIgnoreUse)
	{
		OnUseIgnored(caller);
		return false;
	}
	Toggle();
	OnUse(caller);
	return true;
}

//Stops the door's current movement
void Aprop_move_base::Pause()
{
	bIsClosing = false;
	bIsOpening = false;
}

void Aprop_move_base::SetPosition(float lerp)
{
	//Implemented by children classes
}

float Aprop_move_base::GetPosition() const
{
	return currentLerp;
}

float Aprop_move_base::GetEstimatedTravelTime() const
{
	return movementTime;
}

bool Aprop_move_base::IsOpen()
{
	return (FMath::IsNearlyEqual(currentLerp, 1.0f)
		|| (!IsMoving() && FMath::IsNearlyEqual(1.0f, currentLerp, OPENCLOSE_MEASURE_TOLERANCE)));
}

bool Aprop_move_base::IsClosed()
{
	return (FMath::IsNearlyEqual(currentLerp, 0.0f)
		|| (!IsMoving() && FMath::IsNearlyEqual(0.0f, currentLerp, OPENCLOSE_MEASURE_TOLERANCE)));
}

bool Aprop_move_base::IsOpening() const
{
	return bIsOpening;
}

bool Aprop_move_base::IsClosing() const
{
	return bIsClosing;
}

bool Aprop_move_base::IsMoving() const
{
	return (bIsClosing || bIsOpening);
}
