// Copyright Epic Games, Inc. All Rights Reserved.


#include "DiscreteGameplayGameModeBase.h"

#include "ResourceSpawnerActor.h"


ADiscreteGameplayGameModeBase::ADiscreteGameplayGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADiscreteGameplayGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Spawns the spawner actor straightaway
	const FVector loc = {0, 0, 0};
	const FRotator rot = {0, 0, 0};
	SpawnerActor = GetWorld()->SpawnActor<AResourceSpawnerActor>(AResourceSpawnerActor::StaticClass(), loc, rot);
}

void ADiscreteGameplayGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


