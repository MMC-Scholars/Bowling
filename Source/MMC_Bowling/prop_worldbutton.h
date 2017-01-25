// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "entity_base.h"
#include "prop_movelinear.h"
#include "prop_worldbutton.generated.h"
/**
 * 
 */
UCLASS()
class MMC_BOWLING_API Aprop_worldbutton : public Aprop_movelinear
{
	GENERATED_BODY()

public:


	//Constructor
	Aprop_worldbutton();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public:
	//Presses the button if it is available to be pressed
	UFUNCTION(BlueprintCallable, Category = "prop_worldbutton")
		void Press();

	UFUNCTION(BlueprintImplementableEvent, Category = "prop_worldbutton")
		void OnPressed();

	//Whether or to move the button when pressed
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "prop_worldbutton")
		bool bDontMoveOnPress = true;

	//overrides for opening, to check if we even can move the button
	void Use() override;


private:

	
};
