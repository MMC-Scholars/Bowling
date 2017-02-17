// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.
/*
Purpose: a instantiable helper actor class which on command displays messages onto the screen.
	A little redudant for now, but can be expanded upon with more options later, such as
		screen position options.

@author Michael Trunk
*/
#pragma once

#include "GameFramework/Actor.h"
#include "MMC_Shared.h"
#include "util_debug.h"
#include "info_hudhint.generated.h"

UCLASS()
class MMC_BOWLING_API Ainfo_hudhint : public AActor
{
	GENERATED_BODY()
	
public:	
	//What message to display on screen
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "info_hudhint")
		FText onScreenMessage;

	//How long to display the message for, in seconds
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "info_hudhint", meta=(UIMin = "0.0", UIMax = "9999.0"))
		float displayTime = 5.0f;

	//Color of the message
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "info_hudhint")
		FColor displayColor = FColor::White;

	// Sets default values for this actor's properties
	Ainfo_hudhint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "info_hudhint")
		void setColor(FColor newColor);

	//Prints the message onto the screen
	UFUNCTION(BlueprintCallable, Category = "info_hudhint")
		void displayMessage() const;

	//Static function for printing any info_hudhint onto the screen, given its name
	UFUNCTION(BlueprintCallable, Category = "info_hudhint")
		static void displayHintByName(FName hintName, UObject* WorldContextObject);




	




	
	
};
