// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs
/*
Purpose: entity-derived class which contains additional local methods for representing a bowling pin
	ex. Checking if it has fallen down, moving up and down as if being picked up or reset down

@author Michael Trunk
*/
#pragma once

#include "entity_base.h"
#include "bowling_pin.generated.h"

UCLASS()
class MMC_BOWLING_API Abowling_pin : public Aentity_base
{
	GENERATED_BODY()

public:

#define TOLERANCE_ANGLE		5	//How much angles need to change in order to fall
#define TOLERANCE_LOCATION	10 //How far a pin has to move in order to "fall"

	bool didFall;
	bool isRaisingAndLowering;
	bool isLowering;
	float runningTime; //used for calculating raising and lowering movement

	//Whether or not to have this bowling pin interact with the bowling_system in counting the score
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "bowling_pin")
		bool isInGame = false;

	// Sets default values for this actor's properties
	Abowling_pin();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Checks for significant cahnges in rotation or position
	bool CheckForFallen();

	UFUNCTION(BlueprintCallable, Category = "bowling_pin")
		static Abowling_pin * GetPinClosestToTarget(FName targetName, UObject* WorldContextObject);

	//raises and then lowers the pins
	UFUNCTION(BlueprintCallable, Category = "bowling_pin")
		void RaiseAndLower();

	//Teleports the pins to above their starting locations and then lowers them
	UFUNCTION(BlueprintCallable, Category = "bowling_pin")
		void ResetAndLower();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "bowling_pin")
		float RaiseAndLowerAmplitude = 20.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "bowling_pin")
		float RaiseAndLowerTimeScale = 1.0f;

	//Use these two events to disable physics!
	UFUNCTION(BlueprintImplementableEvent, Category = "bowling_pin")
		void OnRaiseAndLower();

	UFUNCTION(BlueprintImplementableEvent, Category = "bowling_pin")
		void OnResetAndLower();

	UFUNCTION(BlueprintImplementableEvent, Category = "bowling_pin")
		void OnEndRaiseAndLower();

	UFUNCTION(BlueprintImplementableEvent, Category = "bowling_pin")
		void OnEndResetAndLower();
};
