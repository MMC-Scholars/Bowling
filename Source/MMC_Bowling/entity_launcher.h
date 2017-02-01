// Fill out your copyright notice in the Description page of Project Settings.

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

	//Whether or not to immediately launch the projectile on BeginPlay
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "entity_launcher")
		bool bLaunchOnStart = false;

	//Name of the entity_base to launch 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "entity_launcher")
		FName projectileName = TEXT("");

	//Given the name of an entity_base, sets it as projectile
	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void setProjectile(FName newProjectileName);

	//Launches the projectile
	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void launchProjectile(bool teleportBeforeLaunch, bool addToCurrentVelocity);

	//Implementable event for when the projectile is launched
	UFUNCTION(BlueprintImplementableEvent, Category = "entity_launcher")
		void OnLaunch(FVector newVelocity);

	//Override for this entity_base is used - will launch the projectile, teleporting without old velocity
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		virtual void Use() override;




};
