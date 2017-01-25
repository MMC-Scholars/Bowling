// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "info_target.h"
#include "prop_rotator.h"
#include "prop_rotator_pivoted.generated.h"

/**
 * 
 */
UCLASS()
class MMC_BOWLING_API Aprop_rotator_pivoted : public Aprop_rotator
{
	GENERATED_BODY()

protected:
	//Pivot point around which to rotate
	Ainfo_target *target = nullptr;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Name of info_target to pivot around
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "prop_rotator_pivoted")
		FName targetName;

	//Returns refernce to target
	UFUNCTION(BlueprintCallable, Category = "prop_rotator_pivoted")
		Ainfo_target * GetTarget();
	
	//Experimental - sets the target to rotate around
	UFUNCTION(BlueprintCallable, Category = "prop_rotator_pivoted")
		void SetTarget(Ainfo_target *newTarget);

	//Experimental - sets the target to rotate around
	UFUNCTION(BlueprintCallable, Category = "prop_rotator_pivoted")
		void SetTargetByName(FName &newTargetName);

	//Whether or not to auto-parent to target.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "prop_rotator_pivoted")
		bool bParentToTarget = false;

	/*Whether or not to apply the rotation of the pivot to the rotator. Can
	cause teleporting. Does nothing if bParentToTarget is true.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "prop_rotator_pivoted")
		bool bApplyTargetRotation = false;

	//Whether or not to enforce constant distance to target
	//Does nothing if bParentToTarget is true
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "prop_rotator_pivoted")
		bool bApplyTargetPosition = false;

	//Rotates the rotator around the pivot point, to the given lerp value
	UFUNCTION(BlueprintCallable, Category = "prop_rotator_pivoted")
		virtual void SetPosition(float lerp) override;

protected:
	//Private vector and transform information for tracking the pivot point
	FVector locationFromTarget;

	FTransform transformFromTarget;
};
