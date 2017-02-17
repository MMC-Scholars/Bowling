// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.

#include "MMC_Bowling.h"
#include "info_hudhint.h"


// Sets default values
Ainfo_hudhint::Ainfo_hudhint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void Ainfo_hudhint::BeginPlay()
{
	Super::BeginPlay();
	
}

void Ainfo_hudhint::setColor(FColor newColor)
{
	displayColor = newColor;
}

void Ainfo_hudhint::displayMessage(void) const
{
	Autil_debug::PrintMessage(onScreenMessage.ToString(), displayTime, displayColor);
}

void Ainfo_hudhint::displayHintByName(FName hintName, UObject * WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	for (TActorIterator<Ainfo_hudhint> ActorItr(World); ActorItr; ++ActorItr)
	{
		Ainfo_hudhint * curHint = *ActorItr;
		if (curHint && curHint->GetFName() == hintName)
		{
			curHint->displayMessage();
			return;
		}
	}
}

