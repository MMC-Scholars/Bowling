// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#include "MMC_Bowling.h"
#include "EngineUtils.h"
#include "bowling_system.h"


Abowling_system::Abowling_system()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//initialize frames
	Frames = TArray<bowling_frame, FDefaultAllocator>();
	for (int i = 0; i < NUMBER_OF_FRAMES; i++)
		Frames.Emplace(bowling_frame());

	bowling_frame& lastFrame = Frames[Frames.Num() - 1];

	// Make the last frame know that it's the last one
	lastFrame.isLast = true;
}

// Called when the game starts or when spawned
void Abowling_system::BeginPlay()
{
	Super::BeginPlay();

	ResetGame(); //sets defaults
}

// Called every frame
void Abowling_system::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called on BeginPlay();, assigns pins whose names are given to our array of pins
//void AssignPins(); //unused

void Abowling_system::loadScoreTable(TArray<FString>& loadedArray) {
	bowling_highscore_t::loadScoreTableSorted(loadedArray);
}

void Abowling_system::appendNewScore(int iScore, FName playerName) {
	bowling_highscore_t::appendNewScore(iScore, playerName);
}

//Adds extra spaces between the integer score and player name
//returns a new String by value
FString Abowling_system::formatScoreString(const FString & rawInputString)
{
	//get local copy of input
	FString sScore = rawInputString;

	//first check that it's a valid line, otherwise we'll get out-of-bounds stuff.
	if (bowling_highscore_t::verifyScoreLine(sScore)) {
		int iScore = bowling_highscore_t::getScore(sScore);

		//determine number of digits
		int numDigits = 1;
		if (iScore / 100 != 0)
			numDigits = 3;
		else if (iScore / 10 != 0)
			numDigits = 2;

		//get index of middle space
		int spaceIndex = 0;
		sScore.FindChar(' ', spaceIndex);

		//finally, insert the correct number of spaces
		int extraSpaceCount = (BOWLING_SCORE_INTERSPACES - 1) + (3-numDigits);
		for (int i = 0; i < extraSpaceCount; i++)
			sScore.InsertAt(spaceIndex, ' ');
	}
	
	return sScore;
}


//checks the last frames to determine the current endgame type
void Abowling_system::CalculateEndgameType()
{
	
	if (frameIndex <= Frames.Num() - 4) //we're in the ninth frame or before
	{
		endgameType = Undetermined;
		return;
	}
	if (frameIndex == Frames.Num() - 3) //we're in the last normal frame
	{
		bowling_frame& lastNormalFrame = Frames[Frames.Num() - 3];
		if (lastNormalFrame.wasSpare) //if it was a spare
		{
			endgameType = SpareEnding;
			return;
		}
		else if (lastNormalFrame.wasStrike) //if it was a strike
		{
			endgameType = StrikeEnding;
			return;
		}
		else if (lastNormalFrame.GetThrowScore(2) != NOT_THROWN) //if it was neither a strike nor spare
		{
			endgameType = DefaultEnding;
			return;
		}
	}
}

//Checks the last frames to determine if the game is over
bool Abowling_system::CheckForGameover()
{
	bowling_frame& curFrame = Frames[frameIndex];
	bowling_frame& lastFrame = Frames[Frames.Num() - 1];
	bowling_frame& scdLastFrame = Frames[Frames.Num() - 2];

	if (
		curFrame.isLast
		|| (GsetEndgameType() == DefaultEnding)
		|| (GsetEndgameType() == SpareEnding && scdLastFrame.GetThrowScore(1) != NOT_THROWN)
		|| (GsetEndgameType() == StrikeEnding && (lastFrame.GetThrowScore(1) != NOT_THROWN || scdLastFrame.GetThrowScore(2) != NOT_THROWN))
		)
	{
		gameover = true;
		OnGameover();
	}

	return gameover;
}

//calculates all of the absolute scores and absolute native scores for the frames, also handles bScoreIsPending for each frame
void Abowling_system::ReCalculateAbsoluteScores()
{
	//first SET all the absoluteNativeScores to their native scores
	for (int i = 0; i < Frames.Num(); i++)
	{
		Frames[i].GsetAbsoluteNativeScore(Frames[i].GetNativeScore(), OVERRIDE_TYPE_SET);
	}

	//then add strike/spare bonuses to absolute native scores, handling the first 10 frames normally and then handling last 2 specially.
	//also toggles scoreIsPending for all applicable frames
	for (int i = 0; i < Frames.Num() - 2; i++)
	{
		int bonusAmount = 0;
		if (Frames[i].wasStrike && Frames[i + 1].GetThrowScore(1) != NOT_THROWN) //handle strike
		{
			bonusAmount += Frames[i + 1].GetThrowScore(1); //add first throw of next frame...
			if (Frames[i + 1].wasStrike && Frames[i + 2].GetThrowScore(1) != NOT_THROWN) //then add the next throw, of either the second next frame...
			{
				bonusAmount += Frames[i + 2].GetThrowScore(1);
				Frames[i].scoreIsPending = false;
			}

			else if (Frames[i + 1].GetThrowScore(2) != NOT_THROWN) //...or the second throw of the first next frame
			{
				bonusAmount += Frames[i + 1].GetThrowScore(2);
				Frames[i].scoreIsPending = false;
			}

		}
		else if (Frames[i].wasSpare && Frames[i + 1].GetThrowScore(1) != NOT_THROWN) //handle spare
		{
			bonusAmount += Frames[i + 1].GetThrowScore(1);
			Frames[i].scoreIsPending = false;
		}
		else if (!Frames[i].wasSpare && !Frames[i].wasStrike && Frames[i].GetThrowScore(2) != NOT_THROWN) //handle score is pending for closed frames
		{
			Frames[i].scoreIsPending = false;
		}
		//then add the bonus amount
		Frames[i].GsetAbsoluteNativeScore(bonusAmount, OVERRIDE_TYPE_ADD);
	}

	bowling_frame& lastFrame = Frames[Frames.Num() - 1];
	bowling_frame& scdLastFrame = Frames[Frames.Num() - 2];

	//handle last two frames seperately
	{
		int bonusAmount = 0;
		if (scdLastFrame.wasStrike && lastFrame.GetThrowScore(1) != NOT_THROWN)
		{
			bonusAmount += lastFrame.GetThrowScore(1);
			scdLastFrame.scoreIsPending = false;
			lastFrame.scoreIsPending = false; //Could put this in seperate if statement, but this works too.
		}
		scdLastFrame.GsetAbsoluteNativeScore(bonusAmount, OVERRIDE_TYPE_ADD);

		//the last frame's absoluteNativeScore is always just its native score, and we already set that
	}

	//then finally calculate the running count and absolute scores 
	int runningScore = 0;
	for (int i = 0; i < Frames.Num(); i++)
	{
		if (!Frames[i].scoreIsPending)
		{
			runningScore += Frames[i].GsetAbsoluteNativeScore();
			Frames[i].GsetAbsoluteScore(runningScore, OVERRIDE_TYPE_SET);
		}
	}

}

//Returns true if the game is waiting for the user's first throw in the current frame, false otherwise.
bool Abowling_system::WaitingForFirstThrow() const
{
	const bowling_frame& curFrame = Frames[frameIndex];

	return ((!gameover) && curFrame.GetThrowScore(1) == NOT_THROWN);
}

int Abowling_system::GetFallenPinCount() const
{
	int pinCount = 0;
	for (TActorIterator<Abowling_pin> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Abowling_pin * curPin = *ActorItr;
		if (curPin && curPin->isInGame && curPin->didFall)
			pinCount++;
	}
	return pinCount;
}

//Counts the fallen bowling pins, and calculates the score for the current frame.
//calls for the handling of the strike count and strike/spare bonuses
//calls for the re-counting of absoluteScore's
void Abowling_system::CalculateScore()
{
	//never calculate anything if the game is already over
	if (gameover)
		return;

	bowling_frame& curFrame = Frames[frameIndex];

	//find the number of pins that have fallen
	int pinCount = 0;

	for (TActorIterator<Abowling_pin> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Abowling_pin * curPin = *ActorItr;
		if (curFrame.GetThrowScore(1) == NOT_THROWN)
			curPin->didFall = false; //make sure the pins don't remember having fallen if we're in the first throw of the frame
		if (curPin && curPin->isInGame && curPin->CheckForFallen())
			pinCount++;
	}

	//increment the strike count, and call OnStrike()
	{
		if (pinCount == 10)
		{
			strikeCount++;
			OnStrike(strikeCount);
		}
		else
			strikeCount = 0;
	}

	//throw the number of fallen pins to the current frame
	curFrame.Throw(pinCount);

	//Check if we need to call OnSpare
	if (curFrame.wasSpare)
		OnSpare();

	//calculate the endgame type
	CalculateEndgameType();

	//Re-calculate the absolute scores for each frame
	ReCalculateAbsoluteScores();

	//check if the game is over
	CheckForGameover();

	//increment the frame index if we need to
	if ((!gameover) && (curFrame.wasStrike || curFrame.GetThrowScore(2) != NOT_THROWN))
		frameIndex++;
	//otherwise, 

	
}

//Given a frame number and a score type, returns the desired score
int Abowling_system::GetIntScoreOfFrame(int frameNumber, ScoreType type) const
{
	//we'll let blueprinters start from 1
	//frameNumber--;

	//clamp the frame number to avoid out-of-bounds errors
	frameNumber = FMath::Clamp(frameNumber, 0, NUMBER_OF_FRAMES - 1);

	const bowling_frame& curFrame = Frames[frameNumber];

	if (type == FirstThrow)
		return curFrame.GetThrowScore(1);
	if (type == SecondThrow)
		return curFrame.GetThrowScore(2);
	if (type == NativeScore)
		return curFrame.GetNativeScore();
	if (type == AbsoluteNativeScore)
		return curFrame.GetAbsoluteNativeScore();
	if (type == AbsoluteScore)
		return curFrame.GetAbsoluteScore();

	return NOT_THROWN;
}

//Given a frame number and a score type, returns a string representation of the score
FString Abowling_system::GetStringScoreOfFrame(int frameNumber, ScoreType type) const
{

	int iScore = GetIntScoreOfFrame(frameNumber, type);
	const bowling_frame& frame = Frames[frameNumber];

	//handle the last three frames specially
	if (frameNumber >= NUMBER_OF_FRAMES - 3) {
		switch (frameNumber) {
			case (NUMBER_OF_FRAMES - 3): //tenth frame
				if (type == FirstThrow && frame.wasStrike)
					return FString("X");
				break;
			case (NUMBER_OF_FRAMES - 2): //eleventh frame
				if (!Frames[frameNumber - 1].wasStrike)
					return GetStringScoreOfFrame(frameNumber - 1, SecondThrow);
				if (frame.wasStrike)
					return FString("X");
				break;
			case(NUMBER_OF_FRAMES - 1): //final frame
				if (endgameType == SpareEnding) {
					const bowling_frame& preFrame = Frames[frameNumber-1];
					iScore = GetIntScoreOfFrame(frameNumber - 1, FirstThrow); //Just check it here instead of doing nasty recursion
					
					if (preFrame.wasStrike)
						return FString("X");
					if (iScore == 0)
						return FString("-");
					if (iScore == NOT_THROWN)
						return FString(" ");
					return FString::FromInt(iScore);
				}
					
				if (endgameType == StrikeEnding) {
					if (frame.wasStrike)
						return FString("X");
					if (iScore == 0)
						return FString("-");
					if (iScore == NOT_THROWN)
						return FString(" ");
					return FString::FromInt(iScore);
				}
				break;
		}
	}

	FString sScore;

	if (type == AbsoluteScore && Frames[frameNumber].scoreIsPending)
		sScore = FString(TEXT(" "));
	else if (frame.wasSpare && type == SecondThrow)
		sScore = FString(TEXT("/"));
	else if (frame.wasStrike && type == SecondThrow)
		sScore = FString(TEXT("X"));
	else if (frame.wasStrike && type == FirstThrow)
		sScore = FString(TEXT(" ")); //if a frame was a strike, we put in a space for the first throw's spot and put the X in the second throw spot instead
	else if (iScore == 0 && type == AbsoluteScore)
		sScore = FString(TEXT("--"));
	else if (iScore == 0)
		sScore = FString(TEXT("-"));
	else if (iScore == NOT_THROWN)
		sScore = FString(TEXT(" "));
	else
		sScore = FString::FromInt(iScore);

	return sScore;
}

//Returns a string containing the scores of the all the frames
FString Abowling_system::GetStringScoreOfGame() const
{
	FString sScore = FString(TEXT(""));

	if (gameover)
		sScore.Append(TEXT("!"));

	//we start at 0 because the GetScoreOfFrame(...) function does NOT decrement the index - used to start at 1
	for (int i = 0; i < Frames.Num(); i++)
	{
		sScore.Append(GetStringScoreOfFrame(i, FirstThrow));
		sScore.Append(TEXT(" "));

		sScore.Append(GetStringScoreOfFrame(i, SecondThrow));
		sScore.Append(TEXT(" "));

		sScore.Append(GetStringScoreOfFrame(i, AbsoluteScore));
		sScore.Append(TEXT("     "));
	}

	return sScore;
}

//Iterates through all of the pins and raises and lowers those which have not fallen
void Abowling_system::RaiseAndLowerUnfallenPins()
{
	for (TActorIterator<Abowling_pin> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (*ActorItr)
		{
			Abowling_pin * curPin = *ActorItr;
			if (curPin->isInGame && !curPin->didFall)
				curPin->RaiseAndLower();
		}	
	}
}

//Teleports all of the pins above their starting locations and lowers them onto the lane
void Abowling_system::ResetAndLowerAllPins()
{
	//First teleport each of them to a border world
	for (TActorIterator<Abowling_pin> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (*ActorItr)
		{
			Abowling_pin * curPin = *ActorItr;
			if (curPin->isInGame)
				curPin->TeleportToTarget();
		}
	}
	//THEN we teleport them back and reset them
	for (TActorIterator<Abowling_pin> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (*ActorItr)
		{
			Abowling_pin * curPin = *ActorItr;
			if (curPin->isInGame)
				curPin->ResetAndLower();
		}
	}
}

//Resets all the scores of the game
void Abowling_system::ResetGame()
{
	strikeCount = 0;
	frameIndex = 0;
	gameover = false;

	endgameType = Undetermined;

	//reset all frames
	for (int i = 0; i < Frames.Num(); i++)
	{
		Frames[i].ResetFrame();
	}
}

//Returns the total score for the game, i.e. the absolute score of the current frame.
int Abowling_system::GetAbsoluteScore() const
{
	//Clamp it to avoid the last hidden frames
	int index = FMath::Clamp(frameIndex, 0, NUMBER_OF_FRAMES - 3);
	return Frames[index].GetAbsoluteScore();
}

//Gsets the enumerator EndGameType, either DefaultEnding, SpareEnding or StrikeEnding. If it hasn't been determined yet, returns Undetermined.
EndgameType Abowling_system::GsetEndgameType(EndgameType override, const int32 overrideType)
{
	if (overrideType == OVERRIDE_TYPE_SET)
		endgameType = override;
	return endgameType;
}

//Blueprint-able accesor for the most recently calculated EndgameType
EndgameType Abowling_system::GetEndgameType() {
	return endgameType;
}

//Returns the number of the current frame, 1-11
int Abowling_system::GetNumberOfCurrentFrame()
{
	return frameIndex + 1;
}


