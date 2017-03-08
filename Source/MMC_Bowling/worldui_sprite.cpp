// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.
/*
This class is a graphical implementation of the worldui_base. 
It includes a sprite which interacts with the worldui_base's pre-implemented
interface.

@author Michael Trunk
*/

#include "MMC_Bowling.h"
#include "worldui_sprite.h"

Aworldui_sprite::Aworldui_sprite()
{
	//make sure the sprite's location is at the root's location
	if (sprite)
		sprite->SetWorldLocation(this->GetActorLocation());
	else
		printWarning("Failed to load default sprite");
}
