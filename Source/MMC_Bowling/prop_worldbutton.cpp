// Fill out your copyright notice in the Description page of Project Settings.

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
		Press();
		return false;
	}

	OnUse(caller);
	return true;
}

