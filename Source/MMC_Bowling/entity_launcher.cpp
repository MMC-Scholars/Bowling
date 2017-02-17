// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

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
void Aentity_launcher::launchProjectileLinear(bool teleportBeforeLaunch, bool addToCurrentVelocity)
{
	//Don't do anything if our pointer to our projectile is bad
	if (!projectile)
		return;

	//Teleport the object if we need to
	if (teleportBeforeLaunch) {
		projectile->SetActorLocation(this->GetActorLocation());
		projectile->SetActorRotation(launchDirection.Rotation());
	}
	//Then update the launch direction, in case the target has moved
	if (launchTarget)
	{
		setLaunchDirection(GetOffsetToActor(launchTarget));
	}

	//Get value of the old velocity
	FVector oldVelocity = projectile->GetVelocity();

	//Velocity is a speed with a direction - Physics 101
	FVector newVelocity = launchSpeed * launchDirection;
	//then add the original velocity back in if we need to
	if (addToCurrentVelocity)
		newVelocity += oldVelocity;

	//Then the final new velocity is a linear interpolation between oldVelocity and newVelocity
	launchLerp = FMath::Clamp(launchLerp, 0.0f, 1.0f); //clamp the lerp first
	newVelocity = FMath::LerpStable(oldVelocity, newVelocity, launchLerp);

	//Finally actually launch the darn projectile
	if (projectile->EntityModel)
		projectile->EntityModel->SetPhysicsLinearVelocity(newVelocity);

	//Call the implementable event last
	OnLaunch(newVelocity);
}

//Override for this entity_base is used - will launch the projectile, teleporting without old velocity
bool Aentity_launcher::Use(AActor * caller)
{
	if (bIgnoreUse) {
		OnUseIgnored(caller);
		return false;
	}
	
	launchProjectile(true, false);//teleports and does not keep old velocity
	OnUse(caller);
	return true;
}

void Aentity_launcher::launchProjectileAngular(bool teleportBeforeLaunch, bool addToCurrentVelocity)
{
	//Don't do anything if our pointer to our projectile is bad
	if (!projectile)
		return;

	//Teleport the object if we need to
	if (teleportBeforeLaunch) {
		projectile->SetActorLocation(this->GetActorLocation());
		projectile->SetActorRotation(launchDirection.Rotation());
	}
	//Then update the launch direction, in case the target has moved
	if (launchTarget)
	{
		setLaunchDirection(GetOffsetToActor(launchTarget));
	}

	//Get value of the old angular velocity
	FVector oldVelocity = projectile->EntityModel->GetPhysicsAngularVelocity();

	//New angular velocity is as given
	FVector newVelocity = angularLaunchSpeed;
	//see if we need to rotate it to launchDirection
	//I've done the vector math for this
	if (bRotateToLaunchDirection) {
		newVelocity = launchDirection.Rotation().RotateVector(newVelocity);
	}
		
	//then add the original velocity back in if we need to
	if (addToCurrentVelocity)
		newVelocity += oldVelocity;

	//Then the final new velocity is a linear interpolation between oldVelocity and newVelocity
	angularLaunchLerp = FMath::Clamp(angularLaunchLerp, 0.0f, 1.0f); //clamp the lerp first
	newVelocity = FMath::LerpStable(oldVelocity, newVelocity, angularLaunchLerp);

	//Finally actually launch the darn projectile
	if (projectile->EntityModel)
		projectile->EntityModel->SetPhysicsAngularVelocity(newVelocity);
}

//Launches the projectile both linearly and angularly
void Aentity_launcher::launchProjectile(bool teleportBeforeLaunch, bool addToCurrent)
{
	launchProjectileAngular(teleportBeforeLaunch, addToCurrent);
	launchProjectileLinear(false/*never teleport twice*/, addToCurrent);
}
