// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Bowling.h"
#include "worldui_base.h"


// Sets default values
Aworldui_base::Aworldui_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void Aworldui_base::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Aworldui_base::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

#if WITH_EDITOR
void Aworldui_base::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	//Ensure that bActivateOnUse and bUseOnActivate are not both true
	if (bActivateOnUse)
		bUseOnActivate = false;
	if (bUseOnActivate)
		bActivateOnUse = false;
}
#endif //WITH_EDITOR

//The headset's BP class will implement the tracing and calling of this
//Activated when the player looks at this worldui_base
void Aworldui_base::Look(AActor * caller)
{
	//Check if we need to call the other functions
	if (bFocusOnLook)
		Focus(caller);

	if (bActivateOnLook && !(bUseOnLook && bUseOnActivate))
		Activate(caller);

	if (bUseOnLook && !(bActivateOnLook && bActivateOnUse))
		Use(caller);

	//This is the base class, so just call the event for now
	OnLook(caller);
}

//Highlights this worldui_base in some way, to make the user notice it or 'select' it
void Aworldui_base::Focus(AActor * caller)
{
	//This is the base class, so just call the event for now
	OnFocus(caller);
}

//Called to activate the main-purpose function of the worldui_base, ex. quit the game, call something else
void Aworldui_base::Activate(AActor * caller)
{
	//This is the base class, so just call the event for now
	OnActivate(caller);
}

//Override for the entity_base parent function
bool Aworldui_base::Use(AActor * caller)
{
	if (bIgnoreUse)
	{
		OnUseIgnored(caller);
		return false;
	}
		

	if (bActivateOnUse && !bUseOnActivate)
		Activate(caller);

	OnUse(caller);
	return true;
}


