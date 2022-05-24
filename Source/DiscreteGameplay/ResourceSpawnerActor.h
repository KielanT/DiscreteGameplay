// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseFoodActor.h"
#include "EnemyBaseActor.h"
#include "GameFramework/Actor.h"
#include "ResourceSpawnerActor.generated.h"

class ABaseResourceActor;
UCLASS()
class DISCRETEGAMEPLAY_API AResourceSpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceSpawnerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Public variables for getting count of each resource
	int TreeCount = 0;
	int RockCount = 0;
	int IronOreCount = 0;
	int GoldOreCount = 0;

	int FoodCount = 0;

	int EnemyCount = 0;

	//UFUNCTION()
	//	void IncreaseEnemies(); // uses to increate the enemy count for each wave
	
private:
	// Functions for spawning
	void SpawnTrees();
	void SpawnResources();
	void SpawnEnemies();

	// Variables for the actor classes
	TSubclassOf<ABaseResourceActor> TreeActor;
	TSubclassOf<ABaseResourceActor> RockActor;
	TSubclassOf<ABaseResourceActor> IronOreActor;
	TSubclassOf<ABaseResourceActor> GoldOreActor;

	// Variables for the food classes
	TSubclassOf<ABaseFoodActor> FoodActor;

	// Variables for the enemies classes
	TSubclassOf<AEnemyBaseActor> EnemyActor;
	
	const int MAX_RESOURCE_SIZE = 20; // Max resources for each type

	// Bounds for the spawning
	const float MIN_X = -4799.0f;
	const float MAX_X = 4515.0f;
	const float MIN_Y = -4799.0f;
	const float MAX_Y = 4820.0f;
 
	int MaxEnemies = 3; // Sets the maximun enemies and increases every wave (currently removed from implentation)
	
};
