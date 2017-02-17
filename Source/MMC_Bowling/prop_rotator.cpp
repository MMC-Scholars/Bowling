// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

#include "MMC_Bowling.h"
#include "prop_rotator.h"


Aprop_rotator::Aprop_rotator()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aprop_rotator::BeginPlay()
{
	Super::BeginPlay();

	DeltaRotation = InitialDeltaRotation;

	SetSpeed(movementSpeed);

	//Check if we start rotating on spawn
	if (bStartOn)
		Toggle();
	
}

// Called every frame
void Aprop_rotator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//opening and closing processors, called from inside the tick function
void Aprop_rotator::processOpen(float DeltaSeconds)
{
	//first check if we've finished opening the door
	if (!bRotateForever && IsOpen())
	{
		bIsOpening = false;
		OnFullyOpened();
		movementTime = 0.0f;
		return;
	}
	//otherwise just process the movement
	movementTime += DeltaSeconds;

	float deltaLerp = lerpSpeed * DeltaSeconds;
	

	SetPosition(currentLerp + deltaLerp);
}

void Aprop_rotator::processClose(float DeltaSeconds)
{
	//first check if we've finished closing the door
	if (!bRotateForever && IsClosed())
	{
		bIsClosing = false;
		OnFullyClosed();
		movementTime = 0.0f;
		return;
	}
	//otherwise just process the movement
	movementTime += DeltaSeconds;

	float deltaLerp = lerpSpeed * DeltaSeconds;
	
	SetPosition(currentLerp - deltaLerp); //subtract the lerp instead because we're closing the door
}


//Given a 0-1 lerp value, rotates the door between the starting location and the ending location
void Aprop_rotator::SetPosition(float lerp)
{
	//first clamp the lerp value, but don't clamp it if we're rotating forever
	if (!bRotateForever)
		lerp = FMath::Clamp(lerp, 0.0f, 1.0f);

	previousLerp = currentLerp;
	currentLerp = lerp;

	float deltaLerp = currentLerp - previousLerp;

	if (EntityModel)
		EntityModel->AddLocalRotation(deltaLerp * InitialDeltaRotation);
	OnChangePosition(deltaLerp);
}

//Sets a new angular speed as movementSpeed
void Aprop_rotator::SetSpeed(float newSpeed)
{
	movementSpeed = newSpeed;
	lerpSpeed = movementSpeed / DeltaRotation.Euler().Size();
}

//Given a period, calculates the the angular speed and then calls SetSpeed(...)
void Aprop_rotator::SetPeriod(float newPeriod)
{
	SetSpeed(2 * PI / newPeriod);
}


//Accessor functions for booleans
bool Aprop_rotator::IsOpen()
{
	return Super::IsOpen();
}

bool Aprop_rotator::IsClosed()
{
	return Super::IsClosed();
}
