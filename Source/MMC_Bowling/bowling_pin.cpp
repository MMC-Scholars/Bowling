// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Bowling.h"
#include "bowling_pin.h"


// Sets default values
Abowling_pin::Abowling_pin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	didFall = false;
	isRaisingAndLowering = false;
	isLowering = false;

	isInGame = false;
	runningTime = 0.0f;
}

// Called when the game starts or when spawned
void Abowling_pin::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void Abowling_pin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//scale the time to change the seed
	DeltaTime = DeltaTime * RaiseAndLowerTimeScale;

	//Raise and Lower
	if (isRaisingAndLowering)
	{
		runningTime += DeltaTime;
		FVector DeltaLocation = FVector(0.0f);
		float DeltaHeight = (FMath::Sin(runningTime + DeltaTime) - FMath::Sin(runningTime));
		DeltaLocation.Z = DeltaHeight * RaiseAndLowerAmplitude;
		AddActorLocalOffset(DeltaLocation);
		//end the process after enough time
		if (runningTime >= PI)
		{
			ResetWorldTransform(); //make sure we end in the exact initial location
			runningTime = 0; //reset this to avoid bad math later on
			isRaisingAndLowering = false;
			//PrimaryActorTick.bCanEverTick = false;
			OnEndRaiseAndLower();

			//re-enable physics
			EntityModel->SetSimulatePhysics(true);
		}
	}

	//Lower
	if (isLowering)
	{
		runningTime += DeltaTime;
		FVector DeltaLocation = FVector(0.0f);
		float DeltaHeight = (FMath::Sin(runningTime + DeltaTime) - FMath::Sin(runningTime));
		DeltaLocation.Z = -DeltaHeight * RaiseAndLowerAmplitude; //make it negative to go downward
		AddActorLocalOffset(DeltaLocation);
		//end the process after enough time
		if (runningTime >= PI / 2)
		{
			ResetWorldTransform();
			runningTime = 0;
			isLowering = false;
			//PrimaryActorTick.bCanEverTick = false;
			OnEndResetAndLower();

			//re-enable physics
			EntityModel->SetSimulatePhysics(true);
		}
	}

}

// Checks for significant cahnges in rotation or position
bool Abowling_pin::CheckForFallen()
{
	//Never say we just fell if we had already fallen
	if (didFall) //if we're in the first throw of the frame, this is never true as it is set to false in the Abowling_system::CalculateScore()
	{
		didFall = false;
		return false; //never register as falling twice in a row
	}
	if (FMath::Abs(GetActorRotation().Roll - FMath::Abs(OriginalRotation.Roll)) > 10)
		didFall = true;
	if (FMath::Abs(GetActorRotation().Pitch - FMath::Abs(OriginalRotation.Pitch)) > 10)
		didFall = true;
	return didFall;
}

//raises and then lowers the pin in a sine-wave fashion, by enabling the pin's tick
//actual raising and lowering done inside the tick function
void Abowling_pin::RaiseAndLower() 
{
	if (didFall) //don't do this if the pin has fallen
		return;
	if (isLowering) //don't do this if we're already lowering
		return;
	if (isRaisingAndLowering) //don't do this if we're already doing it
		return;

	//disable physics
	EntityModel->SetSimulatePhysics(false);

	isRaisingAndLowering = true;
	//PrimaryActorTick.bCanEverTick = true;
	//these are set back to false from within the tick function

	OnRaiseAndLower(); 
}

//lowers the pin in a sine-wave fashion, by first teleporting the pin to above its starting location
//and then enabling a portion of the tick function
void Abowling_pin::ResetAndLower()
{
	if (didFall) //don't do this if the pin has fallen
		return;
	if (isRaisingAndLowering) //don't do this if we're already raising and lowering
		return;
	if (isLowering) //don't do this if we're already doing it
		return;
	

	//reset position and teleport up
	ResetWorldTransform();
	AddActorLocalOffset(FVector(0.0f, 0.0f, RaiseAndLowerAmplitude));

	OnResetAndLower(); 
	

	isLowering = true;
	PrimaryActorTick.bCanEverTick = true;
	//these are set back to false from within the tick function
}



