// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "entity_base.h"
#include "prop_movelinear.generated.h"

/**
 * 
 */
UCLASS()
class MMC_BOWLING_API Aprop_movelinear : public Aentity_base
{
	GENERATED_BODY()

#define sMOVE_LINEAR "prop_movelinear"
	
	//we'll have private and public copies of this so that we can keep the vector fixed
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = sMOVE_LINEAR)
		FVector InitialDeltaLocation = FVector::ZeroVector;
private:
	FVector DeltaLocation;

	//Fractional lerp value for measuring the open/closed status of a still door
	#define OPENCLOSE_MEASURE_TOLERANCE 0.05f
	#define OPENCLOSE_MOVING_MEASURE_TOLERANCE 0.001f

	//this keeps track of how long we've been opening/closing
	float movementTime = 0.0f;

	//this keeps track of how long we've been waiting
	float waitingTime = 0.0f;

	//booleans for door status
	bool bIsOpening = false;
	bool bIsClosing = false;
	bool bIsWaitingToClose = false;

public:
	//boolean for locked/unlocked state
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = sMOVE_LINEAR)
		bool bIsLocked = false;

private:
	//current lerp value of the door
	float currentLerp = 0.0f;
	//previous lerp value of the door; used for backtracking one tick if we have to
	float previousLerp = 0.0f;

	float lerpSpeed;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = sMOVE_LINEAR)
		float movementSpeed = 50.0f; //in world units/sec 

	//Sets the value of movementSpeed and then recalculates the lerp speed based on the deltaLocation length
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		void SetSpeed(float newSpeed);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = sMOVE_LINEAR)
		float delayBeforeReset = -1.0f; //after opening, the door will automatically close after this amount of time
	
	//Constructor
	Aprop_movelinear();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:
	//opening and closing processors, called from inside the tick function
	void processOpen(float DeltaSeconds);
	void processClose(float DeltaSeconds);
	void processWaitedClose(float DeltaSeconds);

public:
	//public open and close togglers
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		virtual void Open();
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		virtual void Close();
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		virtual void Toggle();

	//Override for entity_base use - calls for toggling the door
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		virtual void Use();

	//Stops the door's current movement
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		void Pause();

	//TODO override for when the door hits something

	//Given a 0-1 lerp value, teleports the door between the starting location and the ending location
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		virtual void SetPosition(float lerp);

	//Returns the current value of currentLerp
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		float GetPosition();

	//Accessor for movement time
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		float GetMovementTime();


	//Accessor functions for booleans
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		bool IsOpen();
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		bool IsClosed();

	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		bool IsOpening();
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		bool IsClosing();
	UFUNCTION(BlueprintCallable, Category = sMOVE_LINEAR)
		bool IsMoving();
	
	//Blueprint implementable events
	UFUNCTION(BlueprintImplementableEvent, Category = sMOVE_LINEAR)
		void OnOpened();

	UFUNCTION(BlueprintImplementableEvent, Category = sMOVE_LINEAR)
		void OnFullyOpened();
	
	UFUNCTION(BlueprintImplementableEvent, Category = sMOVE_LINEAR)
		void OnClosed();

	UFUNCTION(BlueprintImplementableEvent, Category = sMOVE_LINEAR)
		void OnFullyClosed();

	//Called when the door attempts to open or close, but the door is locked
	UFUNCTION(BlueprintImplementableEvent, Category = sMOVE_LINEAR)
		void OnUseLocked();

	//For debugging
	UFUNCTION(BlueprintImplementableEvent, Category = sMOVE_LINEAR)
		void OnChangePosition(float deltaLerp);

};
