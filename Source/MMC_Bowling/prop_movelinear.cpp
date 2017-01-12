// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Bowling.h"
#include "prop_movelinear.h"

//Constructor - nothing to do here
Aprop_movelinear::Aprop_movelinear()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aprop_movelinear::BeginPlay()
{
	Super::BeginPlay();

	//copy public UPROP vector to private copy
	DeltaLocation = InitialDeltaLocation;

	//Call SetSpeed(...) to calculate the initial lerp speed
	SetSpeed(movementSpeed);
}

// Called every frame
void Aprop_movelinear::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsOpening)
		processOpen(DeltaSeconds);
	else if (bIsClosing)
		processClose(DeltaSeconds);
	else if (bIsWaitingToClose)
		processWaitedClose(DeltaSeconds);
}

//Sets the value of movementSpeed and then recalculates the lerp speed based on the deltaLocation length

void Aprop_movelinear::SetSpeed(float newSpeed)
{
	movementSpeed = newSpeed;

	lerpSpeed = movementSpeed / DeltaLocation.Size();
}

//private opening and closing processors, called from inside the tick function
void Aprop_movelinear::processOpen(float DeltaSeconds)
{
	//first check if we've finished opening the door
	if (IsOpen())
	{
		bIsOpening = false;
		OnFullyOpened();
		movementTime = 0.0f;
		return;
	}
	//otherwise just process the movement
	movementTime += DeltaSeconds;
	float DeltaLerp = lerpSpeed * DeltaSeconds;
	SetPosition(currentLerp + DeltaLerp);

}
void Aprop_movelinear::processClose(float DeltaSeconds)
{
	//first check if we've finished closing the door
	if (IsClosed())
	{
		bIsClosing = false;
		OnFullyClosed();
		movementTime = 0.0f;
		return;
	}
	//otherwise just process the movement
	movementTime += DeltaSeconds;
	float DeltaLerp = -lerpSpeed * DeltaSeconds; //use a negative lerp speed to go backwards
	SetPosition(currentLerp + DeltaLerp);
}
void Aprop_movelinear::processWaitedClose(float DeltaSeconds)
{
	waitingTime += DeltaSeconds;
	if (waitingTime >= delayBeforeReset)
		Close();
}


//Open,close, and toggle - the blueprint functions which manipulate the door
void Aprop_movelinear::Open()
{
	//Don't do anything if we're already opening
	if (bIsOpening)
		return;

	//Call the implementable event
	OnOpened();

	//make sure we stop closing and start opening; also start waiting
	bIsClosing = false;
	bIsOpening = true;
	
	//only start waiting if the time to close again is not -1
	if (!FMath::IsNearlyEqual(delayBeforeReset, -1.0f))
		bIsWaitingToClose = true; waitingTime = 0.0f;
	//the tick function will then call for processOpen(...)
}
void Aprop_movelinear::Close()
{
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
void Aprop_movelinear::Toggle()
{
	if (IsOpen() || bIsOpening)
		Close();
	else
		Open(); //this defaults the door to opening when in a paused state
}

//Stops the door's current movement
void Aprop_movelinear::Pause()
{
	bIsClosing = false;
	bIsOpening = false;
}

//Setter function for the lerp - also teleports the door to the appropriate location
void Aprop_movelinear::SetPosition(float lerp)
{
	//first clamp the lerp value
	lerp = FMath::Clamp(lerp, 0.0f, 1.0f);

	previousLerp = currentLerp;
	currentLerp = lerp;

	float deltaLerp = currentLerp - previousLerp;
	//FVector deltaLocation = deltaLerp * InitialDeltaLocation;
	/*
	PrintToScreen(FString::FromInt(static_cast<int>(deltaLocation.X)));
	PrintToScreen(FString::FromInt(static_cast<int>(deltaLocation.Y)));
	PrintToScreen(FString::FromInt(static_cast<int>(deltaLocation.Z)));
	*/
	if (EntityModel)
		EntityModel->AddLocalOffset(deltaLerp * InitialDeltaLocation);
	OnChangePosition(deltaLerp);
}

//Getter function for the lerp value
float Aprop_movelinear::GetPosition()
{
	return currentLerp;
}

//Getter function for the timer for which the door has been moving
float Aprop_movelinear::GetMovementTime()
{
	return movementTime;
}


//Accessor bool functions for the door status
bool Aprop_movelinear::IsOpen()
{
	return (FMath::IsNearlyEqual(currentLerp, 1.0f)
		|| (!IsMoving() && FMath::Abs(1.0 - currentLerp) < OPENCLOSE_MEASURE_TOLERANCE)
		);
}
bool Aprop_movelinear::IsClosed()
{
	return (FMath::IsNearlyEqual(currentLerp, 0.0f)
		|| (!IsMoving() && currentLerp < OPENCLOSE_MEASURE_TOLERANCE)
		);
}

bool Aprop_movelinear::IsOpening()
{
	return bIsOpening;
}
bool Aprop_movelinear::IsClosing()
{
	return bIsClosing;
}
bool Aprop_movelinear::IsMoving()
{
	return (bIsClosing || bIsOpening);
}