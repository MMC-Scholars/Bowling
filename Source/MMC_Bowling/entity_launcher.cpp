// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Bowling.h"
#include "entity_launcher.h"

//Constructor - disables tick
Aentity_launcher::Aentity_launcher()
{
	//Turn of ticking to save performance
	PrimaryActorTick.bCanEverTick = false;
}

//Override for BeginPlay() - does initial calculations regarding given information
void Aentity_launcher::BeginPlay()
{
	Super::BeginPlay();
	//First get references to our friends
	setLaunchDirectionTarget(launchTargetName);
	setProjectile(projectileName);

	//Then see if we need to make our given launch direction unit
	setLaunchDirection(launchDirection);

	//Then launch the projectile at start if we're told to
	if (bLaunchOnStart)
		launchProjectile(true, false); //teleport with new velocity

	/*
	If the launch direction depends on the launchTarget, then the direction is calculated
	at launch-time
	*/
}

//Given a vector, sets the launch direction. If bMakeLaunchDirectionUnit is true, converts input into unit vector
void Aentity_launcher::setLaunchDirection(FVector newDirection)
{
	//First check if we need to make it a unit vector
	if (bMakeLaunchDirectionUnit)
		newDirection = newDirection.GetClampedToSize(0.9999f, 1.0001);
	launchDirection = newDirection;
}

//Given the name of a new info_target, sets the new target for the entity_launcher
void Aentity_launcher::setLaunchDirectionTarget(FName nameOfNewTarget)
{
	Ainfo_target * newTarget = Ainfo_target::FindTargetByName(nameOfNewTarget, this);
	if (newTarget)
	{
		launchTargetName = nameOfNewTarget;
		launchTarget = newTarget;
	}
}

//Given the name of an entity_base, sets it as projectile
void Aentity_launcher::setProjectile(FName newProjectileName)
{
	Aentity_base * newProjectile = this->FindEntityByName(projectileName);
	if (newProjectile)
	{
		projectileName = newProjectileName;
		projectile = newProjectile;
	}
}

//Launches the projectile
void Aentity_launcher::launchProjectile(bool teleportBeforeLaunch, bool addToCurrentVelocity)
{
	//Don't do anything if our pointer to our projectile is bad
	if (!projectile)
		return;

	//Teleport the object if we need to
	if (teleportBeforeLaunch)
		projectile->SetActorLocation(this->GetActorLocation());

	//Then update the launch direction, in case the target has moved
	if (launchTarget)
	{
		setLaunchDirection(GetOffsetToActor(launchTarget));
	}

	//Velocity is a speed with a direction - Physics 101
	FVector newVelocity = launchSpeed * launchDirection;
	//then add the original velocity back in if we need to
	if (addToCurrentVelocity)
		newVelocity += projectile->GetVelocity();

	//Finally actually launch the darn projectile
	if (projectile->EntityModel)
		projectile->EntityModel->SetPhysicsLinearVelocity(newVelocity);

	//Call the implementable event last
	OnLaunch(newVelocity);
}

//Override for this entity_base is used - will launch the projectile, teleporting without old velocity
void Aentity_launcher::Use()
{
	if (!bIgnoreUse)
		launchProjectile(true, false);//teleports and does not keep old velocity
	OnUse();
}
