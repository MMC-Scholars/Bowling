// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MMC_Bowling.h"
#include "GameFramework/Actor.h"
#include "MMC_Shared.h"
#include "entity_base.generated.h"


UCLASS()
class MMC_BOWLING_API Aentity_base : public AActor
{
	GENERATED_BODY()

public:
	//registar of all class instances
	//static TArray<Aentity_base* const*, FDefaultAllocator> registrar;

	//static mesh component
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "entity_base")
	//	TSubobjectPtr<class UStaticMeshComponent> myStaticMeshComponent;
	//UStaticMesh * myStaticMeshObj;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "entity_base")
		UStaticMeshComponent* EntityModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityModel"));

	//Initial world transform of the entity - set in OnBeginPlay()
	FVector OriginalLocation;
	FRotator OriginalRotation;

	//Whether or not to toggle model visibility on BeginPlay
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_base")
		bool bToggleVisibilityOnStart = false;

	// Sets default values for this actor's properties
	Aentity_base();
	//~Aentity_base();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Initial Health Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_base")
		float initialHealth = 100;

	//Health Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_base")
		float health = 100;

	//isDead Property
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "entity_base")
		bool isDead = false;

	//Boolean for whether or not we should destroy the actor 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_base")
		bool destroyOnDeath = false;

	//Float for time delay before destroying after death
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_base")
		float deathDelay = 0;

	//Running clock for checking if we need to destroy this entity
	float deathTime = 0;

	//Function for modifying health
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		virtual void CalculateHealth(float delta);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	//All-purpose extensible use function
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		virtual void Use();

	//Whether or not to allow player to press/use. Child classes must check it themselves
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_base")
		bool bIgnoreUse = true;

	//Extensible use event. Called at the end of Use() function
	UFUNCTION(BlueprintImplementableEvent, Category = "entity_base")
		void OnUse();

	UFUNCTION(BlueprintImplementableEvent, Category = "entity_base")
		void OnKilled();

	//Common C++ function for printing message on screen
	static void PrintToScreen(FString text);

	//Resets the object to its starting location and starting rotation
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		void ResetWorldTransform();

	//Given a name, finds the entity in the world. Can return nullptr so don't use without checking.
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		Aentity_base *FindEntityByName(FName targetName);

	//Given an actor, returns the transform from this target to the given actor
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		FTransform GetTransformToActor(AActor *fromActor);

	//Given an actor, returns the vector offset from this target to the given actor
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		FVector GetOffsetToActor(AActor *fromActor);
	

};
