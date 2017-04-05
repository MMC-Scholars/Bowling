// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

/*
The purpose of this class is to provided additional basic functionalities
to the ATextRenderActor class
*/
#pragma once

#include "Engine/TextRenderActor.h"
#include "info_target.h"
#include "worldui_text.generated.h"

//alias for accessing the text of the text render component
#define RText() GetTextRender()
#define MAX_NAME_LENGTH 12

/**
 * 
 */
UCLASS()
class MMC_BOWLING_API Aworldui_text : public ATextRenderActor
{
	GENERATED_BODY()
	
public:
	Aworldui_text() {
		Clear(); //the constructors for FText are horrid, clumsy
	}

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Aworldui_text")
	void Append(FString suffix, UPARAM(ref) FString & loadedString);

	UFUNCTION(BlueprintCallable, Category = "Aworldui_text")
	void AppendFromTarget(Ainfo_target * target, UPARAM(ref) FString & loadedString);

	//Finds the info_target nearest to the given location and appends its info
	UFUNCTION(BlueprintCallable, Category = "Aworldui_text")
	void AppendFromTargetLocation(FVector targetLocation, UPARAM(ref) FString & loadedString);

	UFUNCTION(BlueprintCallable, Category = "Aworldui_text")
	void BackSpace();

	UFUNCTION(BlueprintCallable, Category = "Aworldui_text")
	void Clear();

	UFUNCTION(BlueprintCallable, Category = "Aworldui_text")
	void Enter(UPARAM(ref) FString & loadedString);

	//Called at the end of Enter();
	UFUNCTION(BlueprintImplementableEvent, Category = "Aworldui_text")
	void OnEnter();

	//Called whenever a worldui_text specific function is called. Not called on SetText(...)
	UFUNCTION(BlueprintImplementableEvent, Category = "Aworldui_text")
	void OnTextChanged();
};
