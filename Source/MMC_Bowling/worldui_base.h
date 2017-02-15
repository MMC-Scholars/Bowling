/*
This class is a base virtual class (i.e., an interface class) which outlines
interactions with an in-world menu item. Similar to Epic's built-in 3D Widget class

Derived classes will have different model/sprite implementation, and different
	purposes.

For each c++ intended Something(...) function, there is a blueprint-extensible
	OnSomething(...) event which is called at the end of the c++ function
	(derived classes will have to enforce this)

@author Michael Trunk
*/

#pragma once

#include "GameFramework/Actor.h"
#include "entity_base.h"
#include "worldui_base.generated.h"

UCLASS()
class MMC_BOWLING_API Aworldui_base : public Aentity_base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aworldui_base();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/*
	Booleans for the different functions interacting with each other
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "worldui_base")
		bool bFocusOnLook = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "worldui_base")
		bool bActivateOnLook = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "worldui_base")
		bool bUseOnLook = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "worldui_base")
		bool bActivateOnUse = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "worldui_base")
		bool bUseOnActivate = false;

	//Helper function ensures that bActivateOnUse and bUseOnActivate will not both be set
	//to true from within the editor
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif //WITH_EDITOR

	//The headset's BP class will implement the tracing and calling of this
	//Activated when the player looks at this worldui_base
	UFUNCTION(BlueprintCallable, Category = "worldui_base")
		virtual void Look(AActor * caller);

	//Blueprint-extensible event called at the end of Look()
	UFUNCTION(BlueprintImplementableEvent, Category = "worldui_base")
		void OnLook(AActor * caller);

	//Highlights this worldui_base in some way, to make the user notice it or 'select' it
	UFUNCTION(BlueprintCallable, Category = "worldui_base")
		virtual void Focus(AActor * caller);

	//Blueprint-extensible event called at the end of Focus()
	UFUNCTION(BlueprintImplementableEvent, Category = "worldui_base")
		void OnFocus(AActor * caller);
	
	//Called to activate the main-purpose function of the worldui_base, ex. quit the game, call something else
	UFUNCTION(BlueprintCallable, Category = "worldui_base")
		virtual void Activate(AActor * caller);

	//Blueprint-extensible event called at the end of Activate()
	UFUNCTION(BlueprintImplementableEvent, Category = "worldui_base")
		void OnActivate(AActor * caller);


	//Override for the entity_base parent function
	UFUNCTION(BlueprintCallable, Category = "worldui_base")
		bool Use(AActor * caller) override;



};
