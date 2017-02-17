// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.
/*
Purpose: extends prop_move_base to provide a sliding door of sorts that moves along a linear direction
	also contains options for sinusoidal movement

@author Michael Trunk
*/

#pragma once

#include "entity_base.h"
#include "prop_move_base.h"
#include "prop_movelinear.generated.h"

/**
 * 
 */
UCLASS()
class MMC_BOWLING_API Aprop_movelinear : public Aprop_move_base
{
	GENERATED_BODY()
	
	//we'll have private and public copies of this so that we can keep the vector fixed
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "prop_movelinear")
		FVector InitialDeltaLocation = FVector::ZeroVector;
private:
	FVector DeltaLocation;

public:
	
	//Sets the value of movementSpeed and then recalculates the lerp speed based on the deltaLocation length
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual void SetSpeed(float newSpeed) override;

	//Constructor
	Aprop_movelinear();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:
	//opening and closing processors, called from inside the tick function
	virtual void processOpen(float DeltaSeconds) override;
	virtual void processClose(float DeltaSeconds) override;

public:
	//Override for entity_base use - calls for toggling the door
	UFUNCTION(BlueprintCallable, Category = "prop_movelinear")
		virtual bool Use(AActor * caller) override;


	//TODO override for when the door hits something

	//Given a 0-1 lerp value, teleports the door between the starting location and the ending location
	UFUNCTION(BlueprintCallable, Category = "prop_movelinear")
		virtual void SetPosition(float lerp) override;


	//Functions and variables for sinusoidal functions
	//These are used in processOpen and processClose to calculate the change in lerp differently
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "prop_movelinear_sinusoidal")
		bool bMoveAsSinusoidalWave = false;

	//Amount of time to open/close in sinusoidal motion
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "prop_movelinear_sinusoidal")
		float sinusoidalQuarterPeriod = 1.0f;	
private:
	//Variable the angular speed based on the half-period
	float angularSpeed;
public:
	//Sets the half-period and recalculates the angular speed from that
	UFUNCTION(BlueprintCallable, Category = "prop_movelinear_sinusoidal")
		void SetQuarterPeriod(float newPeriod);

	

	//Accessor functions for booleans
	UFUNCTION(BlueprintCallable, Category = "prop_movelinear")
		bool IsOpen() override;
	UFUNCTION(BlueprintCallable, Category = "prop_movelinear")
		bool IsClosed() override;

	//Accessor for the estimated time of travel if moving in linear motion
	UFUNCTION(BlueprintCallable, Category = "prop_movelinear")
		float GetEstimatedTravelTime() const override;
	


};
