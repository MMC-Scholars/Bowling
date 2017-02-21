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

#pragma once

#include "worldui_base.h"
#include "Components/BillboardComponent.h"
#include "worldui_sprite.generated.h"

UCLASS()
class MMC_BOWLING_API Aworldui_sprite : public Aworldui_base
{
	GENERATED_BODY()

public:
	//Rendered billboard component
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "worldui_sprite")
		UBillboardComponent * sprite = CreateDefaultSubobject<UBillboardComponent>(TEXT("sprite"));
	
	Aworldui_sprite();
	
	
	
};
