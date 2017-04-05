// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

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

	//Call SetSpeed(...) to calculate the initial lerp speed or whatever else is defined
	SetSpeed(movementSpeed);

	//Call SetHalfPeriod(...) to calculate the initial angular speed
	SetQuarterPeriod(sinusoidalQuarterPeriod);
}

// Called every frame
void Aprop_movelinear::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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

	float DeltaLerp;

	//Get DeltaLerp for sinusoidal motion
	if (bMoveAsSinusoidalWave) {
		DeltaLerp = FMath::Sin(angularSpeed * movementTime) - FMath::Sin(angularSpeed * (movementTime - DeltaSeconds));
	}
	else { //Get DeltaLerp for linear motion
		DeltaLerp = lerpSpeed * DeltaSeconds;
	}
	
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

	float DeltaLerp;

	//Get DeltaLerp for sinusoidal motion
	if (bMoveAsSinusoidalWave) {
		DeltaLerp = FMath::Sin(angularSpeed * movementTime) - FMath::Sin(angularSpeed * (movementTime - DeltaSeconds));
	}
	else { //Get DeltaLerp for linear motion
		DeltaLerp = lerpSpeed * DeltaSeconds;
	}
	SetPosition(currentLerp - DeltaLerp); //subtract the lerp instead because we're closing the door
}


//Override for entity_base use - calls for toggling the door
bool Aprop_movelinear::Use(AActor * caller)
{
	return Super::Use(caller);
}


//Setter function for the lerp - also teleports the door to the appropriate location
void Aprop_movelinear::SetPosition(float lerp)
{
	//first clamp the lerp value
	lerp = FMath::Clamp(lerp, 0.0f, 1.0f);

	previousLerp = currentLerp;
	currentLerp = lerp;

	float deltaLerp = currentLerp - previousLerp;
	
	if (EntityModel)
		EntityModel->AddLocalOffset(deltaLerp * InitialDeltaLocation);
	OnChangePosition(deltaLerp);
}

//Sets the half-period and recalculates the angular speed from that
void Aprop_movelinear::SetQuarterPeriod(float newPeriod)
{
	sinusoidalQuarterPeriod = newPeriod;
	angularSpeed = PI / (2 * sinusoidalQuarterPeriod); //The math actual works out here
}


//Accessor bool functions for the door status
bool Aprop_movelinear::IsOpen()
{
	return ((Super::IsOpen())
		|| (bMoveAsSinusoidalWave && movementTime >= sinusoidalQuarterPeriod) //do an extra check to ensure we don't skip over it
		);
}
bool Aprop_movelinear::IsClosed()
{
	return (Super::IsClosed()
		|| (bMoveAsSinusoidalWave && movementTime >= sinusoidalQuarterPeriod) //do an extra check to ensure we don't skip over it
		);
}

//Accessor for the estimated time of travel if moving in linear motion
float Aprop_movelinear::GetEstimatedTravelTime() const
{
	//Return 0 if we're sinusoidal
	if (bMoveAsSinusoidalWave)
		return 0;

	return InitialDeltaLocation.Size() / movementSpeed;
}
