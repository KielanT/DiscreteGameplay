// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceSpawnerActor.h"
#include "BaseResourceActor.h"
#include "EnemyBaseActor.h"

// Sets default values
AResourceSpawnerActor::AResourceSpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ABaseResourceActor> TreeBP(TEXT("Blueprint'/Game/Blueprints/Tree_BP'"));
	static ConstructorHelpers::FClassFinder<ABaseResourceActor> RockBP(TEXT("Blueprint'/Game/Blueprints/Rock_BP'"));
	static ConstructorHelpers::FClassFinder<ABaseResourceActor> IronOreBP(TEXT("Blueprint'/Game/Blueprints/IronOre_BP'"));
	static ConstructorHelpers::FClassFinder<ABaseResourceActor> GoldOreBP(TEXT("Blueprint'/Game/Blueprints/GoldOre_BP'"));
	
	TreeActor = TreeBP.Class;
	RockActor = RockBP.Class;
	IronOreActor = IronOreBP.Class;
	GoldOreActor = GoldOreBP.Class;

	static ConstructorHelpers::FClassFinder<ABaseFoodActor> FoodBP(TEXT("Blueprint'/Game/Blueprints/BaseFoodActor_BP'"));
	FoodActor = FoodBP.Class;

	static ConstructorHelpers::FClassFinder<AEnemyBaseActor> EnemyBP(TEXT("Blueprint'/Game/Blueprints/EnemyBaseActor_BP'"));
	EnemyActor = EnemyBP.Class;
}

// Called when the game starts or when spawned
void AResourceSpawnerActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnTrees(); // Spawns all the trees at the start
	//SpawnEnemies();  // Spawn all the enemies at the start
	
}

// Called every frame
void AResourceSpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnResources(); // Spawns resources every tick

	// Increases enemy count for next wave and spawns them when all enemies in the current wave has died
	//if(EnemyCount <= 0) 
	//{
	//	MaxEnemies += 2;
	//	SpawnEnemies();
	//}
}

void AResourceSpawnerActor::SpawnTrees()
{
	for(int i = 0; i < MAX_RESOURCE_SIZE; ++i)
	{
		// Spawns all the tries within the bounds
		FVector Location = {FMath::RandRange(MIN_X, MAX_X), FMath::RandRange(MIN_Y, MAX_Y), 200.0f};
		FRotator Rotation = {0.0f, FMath::RandRange(0.0f, 180.0f), 0.0f};
		ABaseResourceActor* actor = GetWorld()->SpawnActor<ABaseResourceActor>(TreeActor, Location, Rotation);
	}
}

void AResourceSpawnerActor::SpawnResources()
{
	
	int num = FMath::RandRange(0, 25); // Used for spawning a specific resource if a certain number is hit (need a better way to get the current percentages)

	// Sets up the location and rotation
	FVector Location = {FMath::RandRange(MIN_X, MAX_X), FMath::RandRange(MIN_Y, MAX_Y), 200.0f};
	FRotator Rotation = {0.0f, FMath::RandRange(0.0f, 180.0f), 0.0f};

	// Spawns the resources depending the number and if there isn't the max resource 
	if(num == 25 && RockCount <= MAX_RESOURCE_SIZE)
	{
		// Spawn Rock
		ABaseResourceActor* actor = GetWorld()->SpawnActor<ABaseResourceActor>(RockActor, Location, Rotation);
		RockCount++;
	}
	else if(num == 15 && IronOreCount <= MAX_RESOURCE_SIZE)
	{
		// Spawn Iron Ore
		ABaseResourceActor* actor = GetWorld()->SpawnActor<ABaseResourceActor>(IronOreActor, Location, Rotation);
		IronOreCount++;
	}
	else if (num == 5 && GoldOreCount <= MAX_RESOURCE_SIZE)
	{
		// Spawn Gold ore
		ABaseResourceActor* actor = GetWorld()->SpawnActor<ABaseResourceActor>(GoldOreActor, Location, Rotation);
		GoldOreCount++;
	}
	else
	{
		if(TreeCount <= MAX_RESOURCE_SIZE) // Always spawns a new tree and food when one is picked up
		{
			// Spawn Tree
			ABaseResourceActor* actor = GetWorld()->SpawnActor<ABaseResourceActor>(TreeActor, Location, Rotation);
			TreeCount++;
		}
		if(FoodCount <= MAX_RESOURCE_SIZE)
		{
			FVector FLocation = {FMath::RandRange(MIN_X, MAX_X), FMath::RandRange(MIN_Y, MAX_Y), 200.0f};
			FRotator FRotation = {0.0f, FMath::RandRange(0.0f, 180.0f), 0.0f};
			ABaseFoodActor* actor = GetWorld()->SpawnActor<ABaseFoodActor>(FoodActor, FLocation, FRotation);
			FoodCount++;
		}
		
	}
}

void AResourceSpawnerActor::SpawnEnemies()
{
	for(int i = 0; i < MaxEnemies; ++i) 
	{
		// Spawns enemy at random location
		FVector FLocation = {FMath::RandRange(MIN_X, MAX_X), FMath::RandRange(MIN_Y, MAX_Y), 200.0f};
		FRotator FRotation = {0.0f, FMath::RandRange(0.0f, 180.0f), 0.0f};
		AEnemyBaseActor* actors = GetWorld()->SpawnActor<AEnemyBaseActor>(EnemyActor, FLocation, FRotation);
		EnemyCount++;
	}
}

