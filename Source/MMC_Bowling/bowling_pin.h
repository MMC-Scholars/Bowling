// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "entity_base.h"
#include "bowling_pin.generated.h"

UCLASS()
class MMC_BOWLING_API Abowling_pin : public Aentity_base
{
	GENERATED_BODY()

public:

	

	bool didFall;
	bool isRaisingAndLowering;
	bool isLowering;
	float runningTime; //used for calculating raising and lowering movement

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "bowling_pin")
		bool isInGame;

	// Sets default values for this actor's properties
	Abowling_pin();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Checks for significant cahnges in rotation or position
	bool CheckForFallen();

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
