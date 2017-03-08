// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs
/*
Purpose: non-spawnable class which contains, manipulates, and retrieves high
	scores for a game of bowling.
	Free functions retrieve and send the data with file.
	Default path for file is "C:\ProgramData\MMC_Bowling\scores.log"

@author Michael Trunk
*/

#pragma once
#include "MMC_Bowling.h"
#include "bowling_shared.h"


#define DEFAULT_HIGHSCORE_PATH		"C:/ProgramData/MMC_Bowling" //Unreal's API supports forward slashes
#define DEFAULT_HIGHSCORE_FILENAME	"scores.log"

/*HIGH SCORE TABLE FILE FORMAT (text-based)
300 AmazingPlayer
290 AlmostAmazingPlayer
250 Pro
200 OneOfMyFriends
170 Me
30 MyChild
0 HadABusToCatch

*/

/*
Retrieves the score table in the form of one long string
*/
FORCEINLINE FString getScoreTableString(const FString& filePath) {
	IPlatformFile& fileReader = FPlatformFileManager::Get().GetPlatformFile();
	
	if (fileReader.FileExists(*filePath)) {
		FString sScoreTable = FString(""); //TODO check how to initialize this!
		if (FFileHelper::LoadFileToString(sScoreTable, *filePath)) {
			return sScoreTable;
		}
	}

	printWarning("Could not find file for high score table!");
	return FString(TEXT(""));
}

class MMC_BOWLING_API bowling_highscore_t
{
public:

	//Appends a new score to file
	static void appendNewScore(int iScore, FName playerName);

	static void loadScoreTableSorted(TArray<FString> & loadedArray) {
		loadScoreTable(loadedArray, DEFAULT_HIGHSCORE_PATH);
		sortScoreTable(loadedArray);
	}
//private:
	//private constructor so this class can't be instantiated
	bowling_highscore_t() {}

	//Writes a string-formatted score table to file
	static void writeScoreTable(const TArray<FString>& scoreTable, const FString& filePath);

	//calls for retrieve score table string from file
	//and then splits it per-line, loading it into the given array
	static void loadScoreTable(TArray<FString>& loadedArray, const FString& filePath);

	//Re-orders elements in the given array so that all of the scores are in order highest to lowest
	//also removes incorrectly formatted lines
	static void sortScoreTable(TArray<FString>& scoreTable);

	//Does what it says, returns true if successful
	static bool verifyOrCreateDirectory(const FString& testDir);

	//Attempts to trim a line and checks that it's valid
	static bool verifyScoreLine(FString& lineItem);

	//Extracts a player's name from a line in the score table
	static FString getPlayerName(const FString& lineItem);

	//Extracts an integer score from a line in the score table
	static int getScore(const FString& lineItem);

	


};