// Fill out your copyright notice in the Description page of Project Settings.

#include "MMC_Bowling.h"
#include "EngineUtils.h"
#include "info_target.h"


// Sets default values
Ainfo_target::Ainfo_target()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Define our root component as our sprite
	//RootComponent = TargetSprite;
}

// Called when the game starts or when spawned
void Ainfo_target::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Ainfo_target::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//This line is necessary to avoid compiler errors
Ainfo_target * Ainfo_target::originTarget;

//Returns the static target located at the origin
//If it does not already exist, creates it
Ainfo_target * Ainfo_target::GetTargetAtOrigin(UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (!originTarget)
	{
		if (World)
			originTarget = World->SpawnActor<class Ainfo_target>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	return originTarget;
}

//Given a name, finds the target in the world.
Ainfo_target * Ainfo_target::FindTargetByName(FName &targetName, UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	for (TActorIterator<Ainfo_target> ActorItr(World); ActorItr; ++ActorItr)
	{
		Ainfo_target * curTarget = *ActorItr;
		if (curTarget && curTarget->GetFName() == targetName)
			return curTarget;
	}
	return nullptr;
}

//Given an actor, returns the transform from this target to the given actor
FTransform Ainfo_target::GetTransformToActor(AActor *fromActor)
{
	if (fromActor)
	{
		return FTransform(fromActor->GetActorRotation() - this->GetActorRotation(), fromActor->GetActorLocation() - this->GetActorLocation());
	}
	else
		return (FTransform());
}

//Given an actor, returns the vector offset from this target to the given actor
FVector Ainfo_target::GetOffsetToActor(AActor *fromActor)
{
	if (fromActor)
		return (fromActor->GetActorLocation()) - (this->GetActorLocation());
	else
		return (FVector::ZeroVector);
}




