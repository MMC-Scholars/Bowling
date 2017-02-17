// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs
/*
Purpose: non-spawnable class which represents and handles a single frame of a bowling game.
	cannot directly interact with the world.
	
@author Michael Trunk
*/



#include "bowling_shared.h"
#include "MMC_Shared.h"
#pragma once


/** bowling_frame - subsystem entity which represents and handles a single frame of the bowling
*  scoring system
*/
class MMC_BOWLING_API bowling_frame
{


private:
	//the score of this frame including the scores of the previous frames and all strike/spare bonuses. There is a gset function for this
	//but the value is otherwise not handled from within the class itself.
	int absoluteScore;


	int absoluteNativeScore;
	int nativeScore;

	//these two default to -1, meaning that they haven't been thrown
	int firstThrow;
	int secondThrow;


public:

	//default this to false. This is only set true for the last frame in the array
	bool isLast;

	bool scoreIsPending;

	bool wasStrike;
	bool wasSpare;


	bowling_frame();
	~bowling_frame();

	//adds to the firstThrow or secondThrow amount, depending, and handles sets wasStrike/wasSpare accordingly
	void Throw(int amount);

	//resets the frame to default, empty values
	void ResetFrame();

	//Given a throw number, returns the score of that throw
	int GetThrowScore(int throwNumber);

	//Gets the number of points scored during this frame, excluding strike/spare bonus
	int GetNativeScore();

	//Gsets the total number of points for this frame, including strike/spare bonus 
	int GsetAbsoluteNativeScore(int override = 0, int overrideType = OVERRIDE_TYPE_NULL);

	//Gsets the total number of points for this frame, including strike/spare bonus and all previous frames.
	//this is to be handled only by the bowling_system entity, not internally
	int GsetAbsoluteScore(int override = 0, int overrideType = OVERRIDE_TYPE_NULL);
};
