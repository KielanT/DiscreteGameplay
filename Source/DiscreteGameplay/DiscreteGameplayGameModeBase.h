// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DiscreteGameplayGameModeBase.generated.h"

class AResourceSpawnerActor;
/**
 * 
 */
UCLASS()
class DISCRETEGAMEPLAY_API ADiscreteGameplayGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADiscreteGameplayGameModeBase();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY()
		AResourceSpawnerActor* SpawnerActor; 

};
