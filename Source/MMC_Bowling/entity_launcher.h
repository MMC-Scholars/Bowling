/*
Purpose: an invisible point entity which can on command set the motion of a named entity_base projectile
	Can control both linear and angular velocities
	Has several options for teleporting and maintaining the old velocities

@author Michael Trunk
*/
#pragma once

#include "entity_base.h"
#include "entity_launcher.generated.h"

/**
 * 
 */
UCLASS()
class MMC_BOWLING_API Aentity_launcher : public Aentity_base
{
	GENERATED_BODY()
	
public:
	//Constructor - disables tick
	Aentity_launcher();

	//Override for BeginPlay() - does initial calculations regarding given information
	virtual void BeginPlay() override;

	//Direction to launch the ball in. Also acts as scalar for the launch velocity
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "entity_launcher")
		FVector launchDirection = FVector::ZeroVector;

	//Whether or not to force the launch direction to be unit
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "entity_launcher")
		bool bMakeLaunchDirectionUnit = true;

	//Given a vector, sets the launch direction. If bMakeLaunchDirectionUnit is true, converts input into unit vector
	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void setLaunchDirection(FVector newDirection);

	//If specified, the launch will always point towards this info_target instead of using launchDirection
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "entity_launcher")
		FName launchTargetName = TEXT("");

	//Given the name of a new info_target, sets the new target for the entity_launcher
	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void setLaunchDirectionTarget(FName nameOfNewTarget);

private:
	/*
	Both of these private pointers are (attemptingly) set to their correct values on BeginPlay()
	*/
	Ainfo_target * launchTarget = nullptr; //private pointer to the launch target

	Aentity_base * projectile = nullptr; //private pointer to the projectile 
public:
	
	//In world units/second
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_launcher")
		float launchSpeed = 10.0f;

	//Linear interpolation between old velocity and new velocity on launch. Old is 0, new is 1
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_launcher")
		float launchLerp = 1.0f;

	//Whether or not to immediately launch the projectile on BeginPlay
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "entity_launcher")
		bool bLaunchOnStart = false;

	//Name of the entity_base to launch 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "entity_launcher")
		FName projectileName = TEXT("");

	//Given the name of an entity_base, sets it as projectile
	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void setProjectile(FName newProjectileName);

	//Launches the projectile in the given linear direction
	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void launchProjectileLinear(bool teleportBeforeLaunch, bool addToCurrentVelocity);

	//Implementable event for when the projectile is launched
	UFUNCTION(BlueprintImplementableEvent, Category = "entity_launcher")
		void OnLaunch(FVector newVelocity);

	//Override for this entity_base is used - will launch the projectile, teleporting without old velocity
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		virtual void Use() override;


	/*
	Optional angular launching - sets the projectile's angular velocity
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_launcher_angular")
		FVector angularLaunchSpeed = FVector::ZeroVector;

	//Linear interpolation between old and new angular velocities on launch. Old is 0, new is 1
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_launcher_angular")
		float angularLaunchLerp = 1.0f;

	//If true, the new angular velocity will rotate around the LaunchDirection on launch-time
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_launcher_angular")
		bool bRotateToLaunchDirection = false;

	//Launches the projectile into the angular velocity
	UFUNCTION(BlueprintCallable, Category = "entity_launcher_angular")
		void launchProjectileAngular(bool teleportBeforeLaunch, bool addToCurrentVelocity);


	

	//Launches the projectile both linearly and angularly
	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void launchProjectile(bool teleportBeforeLaunch, bool addToCurrent);




};
