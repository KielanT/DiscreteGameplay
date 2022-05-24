// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "Components/ActorComponent.h"
#include "BattleComponent.generated.h"


class UXPComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISCRETEGAMEPLAY_API UBattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		bool GetTurn() { return bIsPlayersTurn; } // Used for checking if its the players turn or the enemies

	UFUNCTION(BlueprintCallable)
		bool GetPlayerHit() { return bPlayerHit; } // Checks if the player has hit the enemy or not

	UFUNCTION(BlueprintCallable)
		void PlayerAttack(); // Used for attacking the enemy when the button in the UI is hit

	UFUNCTION(BlueprintCallable)
		void EnemyStartAttack(); // Starts timer when ready to attack the player
	
	UFUNCTION(BlueprintCallable)
		float GetEnemyHealthBar() { return EnemyHealthBar; } // Returns the enemy health bar value

	UFUNCTION(BlueprintCallable)
			bool GetEnemyHit() { return bEnemyHit; } // Checks if the enemy has hit the player
	
private:

	UFUNCTION()
		void EnemyAttack(); // Attack the player when timer is up
	
	UPROPERTY()
		bool bIsPlayersTurn = true; // Checks if it's players turn or enemies

	const int MAX_ENEMY_HEALTH = 80; // Constant for max health for enemy

	UPROPERTY()
		int EnemyHealth = MAX_ENEMY_HEALTH; // Sets the enemy health to the max
	
	UPROPERTY()
		int SwordDamage = 10; // The damage done by the sword

	UPROPERTY()
		float EnemyHealthBar = 1.0f; // Sets the value of the health bar

	UPROPERTY()
		bool bPlayerHit; // Variable for if the player hits or not
	
	UPROPERTY()
		bool bEnemyHit; // Variable for if the Enemy hits or not

	UPROPERTY()
		FTimerHandle Timer; // Handle for the timer
	
	UPROPERTY()
		float Duration = 3.0f; // Duration of the timer

	UPROPERTY()
		APawn* Player; // Used for getting access to the player and its components

	UPROPERTY()
		UHealthComponent* HealthComponent; // Stores the health component
	
	UPROPERTY()
		int DoOnce = 0; // Used for only running the timer once when needed

	UPROPERTY()
	UXPComponent* XPComp; // Stores the xp component 
};
