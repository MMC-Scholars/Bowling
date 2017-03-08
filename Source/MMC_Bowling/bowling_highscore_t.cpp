#include "MMC_Bowling.h"
#include "bowling_highscore_t.h"

//Appends a new score to file
void bowling_highscore_t::appendNewScore(int iScore, FName playerName)
{
	TArray<FString> scoreTable = TArray<FString>();
	loadScoreTableSorted(scoreTable);
	scoreTable.Add(FString::FromInt(iScore) + " " + playerName.ToString() + "\n");
	writeScoreTable(scoreTable, DEFAULT_HIGHSCORE_PATH);
}

//Writes a string-formatted score table to file
void bowling_highscore_t::writeScoreTable(const TArray<FString>& scoreTable, const FString & filePath)
{
	if (verifyOrCreateDirectory(filePath)) {
		//Recompose one long string from the TArray
		FString sScoreTable = "";
		for (int i = 0; i < scoreTable.Num(); i++)
			sScoreTable += scoreTable[i] + "\n";
	
		FString absoluteFilePath = filePath + "/" + DEFAULT_HIGHSCORE_FILENAME;

		FFileHelper::SaveStringToFile(sScoreTable, *absoluteFilePath);
	}
	else {
		printWarning("Failed to create directory for high score table!");
	}
}

//calls for retrieve score table string from file
//and then splits it per-line, loading it into the given array
void bowling_highscore_t::loadScoreTable(TArray<FString>& loadedArray, const FString & filePath)
{
	//Retrieve score table in the form of one long string
	FString scoreTable = getScoreTableString(filePath + "/" + DEFAULT_HIGHSCORE_FILENAME);

	//Estimate the length of the TArray to avoid constant re-locating
	loadedArray.Reserve(scoreTable.Len() / 16);

	scoreTable.ParseIntoArrayLines(loadedArray);
}

//Removes invalid lines and then sorts them via selection sort
void bowling_highscore_t::sortScoreTable(TArray<FString>& scoreTable)
{
	//iterate through it once to pop invalids
	for (int i = 0; i < scoreTable.Num(); i++) {
		FString & curLine = scoreTable[i];
		if (!verifyScoreLine(curLine)) {
			scoreTable.RemoveAt(i);
		}
	}

	int max = 0;
	int maxIndex = 0;
	for (int i = 0; i < scoreTable.Num(); i++) {
		//iterate through the non-sortedto get the next max
		for (int j = i; j < scoreTable.Num(); j++) {
			FString & curLine = scoreTable[j];//alias
			int testMax = getScore(curLine);
			if (testMax > max) {
				max = testMax;
				maxIndex = j;
			}
		}
		scoreTable.Swap(i, maxIndex);
	}
}

//Does what it says, returns true if successful
bool bowling_highscore_t::verifyOrCreateDirectory(const FString & testDir)
{
	// Every function call, unless the function is inline, adds a small
	// overhead which we can avoid by creating a local variable like so.
	// But beware of making every function inline!
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Directory Exists?
	if (!PlatformFile.DirectoryExists(*testDir))
	{
		PlatformFile.CreateDirectory(*testDir);

		if (!PlatformFile.DirectoryExists(*testDir))
		{
			return false;
			//~~~~~~~~~~~~~~
		}
	}
	return true;
}

//Trims and checks that a line in the score table is a valid line
bool bowling_highscore_t::verifyScoreLine(FString & lineItem)
{
	//assume true, then do checks
	bool bIsValid = true;

	lineItem.Trim();

	//Epic's own trim function doesn't trim off trailing spaces, so we'll do that ourselves
	while (lineItem.EndsWith(FString(" "))) {
		if (lineItem.IsValidIndex(lineItem.Len()))
			lineItem.RemoveAt(lineItem.Len());
		else {
			printWarning(TEXT("Attemped to access out-of-bounds index while trimming a high score FString!"));
			bIsValid = false;
			break;
		}	
	}

	//first check that we have a space in the middle
	int spaceIndex = 0;
	if (!lineItem.FindChar(' ', spaceIndex))
		bIsValid = false;

	//check that the first part of the string is numeric
	if (!lineItem.Mid(0, spaceIndex).IsNumeric()) {
		printWarning(TEXT("Failed to verify score substring as an integer!"));
		bIsValid = false;
	}

	return bIsValid;
}

//Extracts a player's name from a line in the score table
FString bowling_highscore_t::getPlayerName(const FString & lineItem)
{
	int spaceIndex = 0;
	if (lineItem.FindChar(' ', spaceIndex))
		return lineItem.Mid(spaceIndex + 1); //rip it right out of the string

	//uh-oh! something happenned! verifyScoreLine would print the error message
	return FString("");
}

//Extracts an integer score from a line in the score table
int bowling_highscore_t::getScore(const FString & lineItem)
{
	int spaceIndex = 0;
	if (lineItem.FindChar(' ', spaceIndex))
		return FCString::Atoi(*(lineItem.Mid(0, spaceIndex))); //rip it right out of the string

	//uh-oh! something happenned! verifyScoreLine would print the error message
	return 0;
}


