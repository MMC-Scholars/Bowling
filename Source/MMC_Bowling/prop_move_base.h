// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "entity_base.h"
#include "prop_move_base.generated.h"

/**
 * 
 */
UCLASS()
class MMC_BOWLING_API Aprop_move_base : public Aentity_base
{
	GENERATED_BODY()

//Fractional lerp value for measuring the open/closed status of a still door
#define OPENCLOSE_MEASURE_TOLERANCE 0.05f
#define OPENCLOSE_MOVING_MEASURE_TOLERANCE 0.001f
	
protected:
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "prop_move_base")
		bool bIsLocked = false;

protected:
	//current lerp value of the door
	float currentLerp = 0.0f;
	//previous lerp value of the door; used for backtracking one tick if we have to
	float previousLerp = 0.0f;

	float lerpSpeed;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "prop_move_base")
		float movementSpeed = 50.0f; //in world units/sec 

	//Sets the value of movementSpeed and then recalculates the lerp speed based on the deltaLocation length
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual void SetSpeed(float newSpeed);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "prop_move_base")
		float delayBeforeReset = -1.0f; //after opening, the door will automatically close after this amount of time

	//Constructor
	Aprop_move_base();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds);

protected:
	//opening and closing processors, called from inside the tick function
	virtual void processOpen(float DeltaSeconds);
	virtual void processClose(float DeltaSeconds);
	virtual void processWaitedClose(float DeltaSeconds);

public:
	//public open and close togglers
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual void Open();
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual void Close();
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual void Toggle();

	//Override for entity_base use - calls for toggling the door
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual void Use() override;

	//Stops the door's current movement
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual void Pause();

	//TODO override for when the door hits something

	//Given a 0-1 lerp value, teleports the door between the starting location and the ending location
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual void SetPosition(float lerp);

	//Returns the current value of currentLerp
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual float GetPosition() const;

	//Accessor for movement time
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual float GetMovementTime() const;



		//Accessor functions for booleans
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual bool IsOpen();
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual bool IsClosed();

	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual bool IsOpening() const;
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual bool IsClosing() const;
	UFUNCTION(BlueprintCallable, Category = "prop_move_base")
		virtual bool IsMoving() const;

	//Blueprint implementable events
	UFUNCTION(BlueprintImplementableEvent, Category = "prop_move_base")
		void OnOpened();

	UFUNCTION(BlueprintImplementableEvent, Category = "prop_move_base")
		void OnFullyOpened();

	UFUNCTION(BlueprintImplementableEvent, Category = "prop_move_base")
		void OnClosed();

	UFUNCTION(BlueprintImplementableEvent, Category = "prop_move_base")
		void OnFullyClosed();

	//Called when the door attempts to open or close, but the door is locked
	UFUNCTION(BlueprintImplementableEvent, Category = "prop_move_base")
		void OnUseLocked();

	//For debugging
	UFUNCTION(BlueprintImplementableEvent, Category = "prop_move_base")
		void OnChangePosition(float deltaLerp);
	
	
};
