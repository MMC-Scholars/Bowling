// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "info_target.generated.h"

UCLASS()
class MMC_BOWLING_API Ainfo_target : public AActor
{
	GENERATED_BODY()
	
public:	
	//Hard-coded sprite component
	/*
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "info_target")
		UPaperSpriteComponent* TargetSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TargetSprite"));
	*/
	// Sets default values for this actor's properties
	Ainfo_target();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Static pointer to target at the world origin
	static Ainfo_target *originTarget;

	//Returns the static target located at the origin
	UFUNCTION(BlueprintCallable, Category = "info_target")
		static Ainfo_target *GetTargetAtOrigin(UObject* WorldContextObject);

	//Given a name, finds the target in the world.
	UFUNCTION(BlueprintCallable, Category = "info_target")
		static Ainfo_target *FindTargetByName( UPARAM(ref) FName &targetName, UObject* WorldContextObject);

	//Given an actor, returns the transform from this target to the given actor
	UFUNCTION(BlueprintCallable, Category = "info_target")
		FTransform GetTransformToActor(AActor *fromActor);

	//Given an actor, returns the vector offset from this target to the given actor
	UFUNCTION(BlueprintCallable, Category = "info_target")
		FVector GetOffsetToActor(AActor *fromActor);
	
	
};
