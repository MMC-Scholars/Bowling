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

	UFUNCTION(BlueprintImplementableEvent, Category = "entity_base")
		void OnKilled();

	//Common C++ function for printing message on screen
	static void PrintToScreen(FString text);



	//Resets the object to its starting location and starting rotation
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		void ResetWorldTransform();

	

};
