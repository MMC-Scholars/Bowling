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
	UPROPERTY(BlueprintReadOnly, Category = "entity_launcher")
		FName launchDirectionTarget = TEXT("");

	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void setLaunchDirectionTarget(FName nameOfNewTarget);

private:
	Ainfo_target * launchTarget = nullptr; //private reference to the launch target
public:
	
	//In world units/second
	UPROPERTY(BlueprintReadWrite, Category = "entity_launcher")
		float launchSpeed = 10.0f;

	//Name of the entity_base to launch 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "entity_launcher")
		FName projectileName = TEXT("");

	//Launches the projectile
	UFUNCTION(BlueprintCallable, Category = "entity_launcher")
		void launchProjectile(bool teleportBeforeLaunch);



};
