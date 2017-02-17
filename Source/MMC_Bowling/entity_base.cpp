// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs.


#include "MMC_Bowling.h"
#include "entity_base.h"


// Sets default values
Aentity_base::Aentity_base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Define our root component as our static mesh
	RootComponent = EntityModel;

};

// Called when the game starts or when spawned
void Aentity_base::BeginPlay()
{
	Super::BeginPlay();

	//first see if we need to teleport to the spawnTargetName
	Ainfo_target * spawnTarget = Ainfo_target::FindTargetByName(spawnTargetName, this);
	if (spawnTarget)
	{
		SetActorLocation(spawnTarget->GetActorLocation());
	}

	OriginalLocation = this->GetActorLocation();
	OriginalRotation = this->GetActorRotation();
	health = initialHealth;
	deathTime = 0;
	CalculateHealth(0); //check if we're dead at the start

	//Check if mapper wants us to toggle visibility on start
	if (bToggleVisibilityOnStart)
		EntityModel->ToggleVisibility();
}

// Called every frame
void Aentity_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDead && destroyOnDeath)
	{
		deathTime += DeltaTime;
		if (deathTime > deathDelay)
		{
			PrimaryActorTick.bCanEverTick = true;
			Destroy();
		}
	}
}

//Teleports the entity to the info_target named in the object settings
void Aentity_base::TeleportToTarget()
{
	Ainfo_target * teleportTarget = Ainfo_target::FindTargetByName(teleportTargetName, this);
	if (teleportTarget)
	{
		SetActorTransform(teleportTarget->GetActorTransform());
	}
}

void Aentity_base::CalculateHealth(float delta)
{
	//Don't ever process health for objects who start with 0 health
	if (initialHealth == 0)
		return;
	health += delta;

	//Check if we're dead or not
	if (health < 0)
	{
		isDead = true;
		OnKilled();
	}
	else
		isDead = false;

	//Check if we need to start the destroy countdown
	if (isDead && destroyOnDeath)
	{
		PrimaryActorTick.bCanEverTick = true;
	}

}

#if WITH_EDITOR
//Helper function for cleaner updating in the editor
void Aentity_base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	isDead = false;
	initialHealth = 100;

	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Check if we're dead
	CalculateHealth(0);
}
#endif

//All-purpose extensible use function
bool Aentity_base::Use(AActor * caller)
{
	if (bIgnoreUse)
	{
		OnUseIgnored(caller);
		return false;
	}
		
	OnUse(caller);
	return true;
}

//Stops all movement and teleports object to its orginal position; ignores local offset
void Aentity_base::ResetWorldTransform()
{
	EntityModel->SetPhysicsLinearVelocity(FVector::ZeroVector);
	EntityModel->SetPhysicsAngularVelocity(FVector::ZeroVector);

	SetActorLocation(OriginalLocation);
	SetActorRotation(OriginalRotation);
}

//Given a name, finds the actor in the world. Can return nullptr
AActor * Aentity_base::FindActorByName(FName targetName, UObject const * const WorldContextObject)
{
	if (WorldContextObject)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
		for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
		{
			AActor * curActor = *ActorItr;
			if (curActor && curActor->GetFName() == targetName)
				return curActor;
		}
		printWarning(FString("Failed to fine actor ") + targetName.ToString());
	}
	return nullptr;
}

//Given a name, finds the entity in the world. Can return nullptr
Aentity_base * Aentity_base::FindEntityByName(FName targetName)
{
	if (targetName == FName("None"))
		return nullptr;
	
	for (TActorIterator<Aentity_base> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Aentity_base * curEntity = *ActorItr;
		if (curEntity && curEntity->GetFName() == targetName)
			return curEntity;
	}
	printWarning(FString("Failed to fine entity ") + targetName.ToString());
	return nullptr;
}

//Given an actor, returns the transform from this target to the given actor
FTransform Aentity_base::GetTransformToActor(AActor *fromActor)
{
	if (fromActor)
	{
		return FTransform(fromActor->GetActorRotation() - this->GetActorRotation(), fromActor->GetActorLocation() - this->GetActorLocation());
	}
	else
		return (FTransform());
}

//Given an actor, returns the vector offset from this target to the given actor
FVector Aentity_base::GetOffsetToActor(AActor *fromActor)
{
	if (fromActor)
		return (fromActor->GetActorLocation()) - (this->GetActorLocation());
	else
		return (FVector::ZeroVector);
}

