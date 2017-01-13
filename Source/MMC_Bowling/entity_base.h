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

#define sENTITY_BASE "entity_base"

public:
	//registar of all class instances
	//static TArray<Aentity_base* const*, FDefaultAllocator> registrar;

	//static mesh component
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "entity_base")
	//	TSubobjectPtr<class UStaticMeshComponent> myStaticMeshComponent;
	//UStaticMesh * myStaticMeshObj;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = sENTITY_BASE)
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = sENTITY_BASE)
		float initialHealth = 100;

	//Health Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = sENTITY_BASE)
		float health = 100;

	//isDead Property
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = sENTITY_BASE)
		bool isDead = false;

	//Boolean for whether or not we should destroy the actor 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = sENTITY_BASE)
		bool destroyOnDeath = false;

	//Float for time delay before destroying after death
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = sENTITY_BASE)
		float deathDelay = 0;

	//Running clock for checking if we need to destroy this entity
	float deathTime = 0;

	//Function for modifying health
	UFUNCTION(BlueprintCallable, Category = sENTITY_BASE)
		virtual void CalculateHealth(float delta);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	//All-purpose extensible use function
	UFUNCTION(BlueprintCallable, Category = sENTITY_BASE)
		virtual void Use();

	//Whether or not to allow player to press/use. Child classes must check it themselves
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = sENTITY_BASE)
		bool bIgnoreUse = true;

	//Extensible use event. Called at the end of Use() function
	UFUNCTION(BlueprintImplementableEvent, Category = sENTITY_BASE)
		void OnUse();

	UFUNCTION(BlueprintImplementableEvent, Category = sENTITY_BASE)
		void OnKilled();

	//Common C++ function for printing message on screen
	static void PrintToScreen(FString text);



	//Resets the object to its starting location and starting rotation
	UFUNCTION(BlueprintCallable, Category = sENTITY_BASE)
		void ResetWorldTransform();

	

};
