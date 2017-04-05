// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf or contact The Ohio State University Office of Legal Affairs

#include "MMC_Bowling.h"
#include "worldui_text.h"

void Aworldui_text::BeginPlay() {
	Clear();
}

//also checks for capitalizing the first letter
void Aworldui_text::Append(FString suffix, FString & loadedString) {
	FString tmp = RText()->Text.ToString();

	//first check against enter and backspace inputs
	if (suffix.Equals(FString("Enter"), ESearchCase::IgnoreCase)) {
		Enter(loadedString);
		return;
	}
	if (suffix.Equals(FString("Back"), ESearchCase::IgnoreCase)) {
		BackSpace();
		return;
	}

	if (tmp.Len() == 0)
		suffix = suffix.ToUpper();
	//cap length of name to 12 characters
	if (tmp.Len() >= MAX_NAME_LENGTH)
		return;

	RText()->SetText(FText::FromString(tmp + suffix));
	OnTextChanged();
}

//Appends the information from a given Ainfo_target
void Aworldui_text::AppendFromTarget(Ainfo_target * target, FString & loadedString) {
	if (target)
		Append(target->GetInfo(), loadedString);
}

void Aworldui_text::AppendFromTargetLocation(FVector targetLocation, FString & loadedString) {
	AppendFromTarget(Ainfo_target::FindTargetNearestToLocation(targetLocation, this), loadedString);
}

void Aworldui_text::BackSpace() {
	FString tmp = RText()->Text.ToString();
	int length = tmp.Len();
	if (length > 0){
		tmp.RemoveAt(length - 1);
		RText()->SetText(FText::FromString(tmp));
		OnTextChanged();
	}
}

void Aworldui_text::Enter(FString & loadedString) {
	FString tmp = RText()->Text.ToString();

	//check again empty string
	if (tmp.Len() == 0)
		return;

	loadedString = RText()->Text.ToString();
	OnEnter();
}

void Aworldui_text::Clear() {
	RText()->SetText(FText::FromString(FString("")));
	OnTextChanged();
}