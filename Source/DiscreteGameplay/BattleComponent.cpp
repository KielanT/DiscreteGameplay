// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleComponent.h"

#include "Kismet/GameplayStatics.h"
#include "XPComponent.h"

// Sets default values for this component's properties
UBattleComponent::UBattleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBattleComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Gets player
	HealthComponent = Player->FindComponentByClass<UHealthComponent>(); // Gets the component
	//XPComp = Player->FindComponentByClass<UXPComponent>(); // Gets the component
}


// Called every frame
void UBattleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		// ...
}

void UBattleComponent::PlayerAttack()
{
	int num = FMath::RandRange(1, 10); // Used for getting a random value for determining if the player has hit or missed

	
	if(num >= 1 && num <= 6) // The player has a 60% chance of hitting
	{
		EnemyHealth -= SwordDamage; // Removes health from the enemy
		float difference = EnemyHealthBar - ((float)EnemyHealth / float(MAX_ENEMY_HEALTH)); // Calculates how much should be removed from the health bar
		EnemyHealthBar -= difference; // Removes from the health bar
		bPlayerHit = true; // The player his hit
		//XPComp->AddXP(FMath::RandRange(1, 5)); // Adds XP when a succesful hit has happend (Removed because for some reason it breaks it)
	}
	else
	{
		bPlayerHit = false; // The Player has missed
	}
	bIsPlayersTurn = false; // Sets the enemies turn
}

void UBattleComponent::EnemyStartAttack()
{
	DoOnce++; // Increases every frame to only do once when function called
	if(!bIsPlayersTurn && DoOnce <= 1) // Checks if its the enemies turn and if its been called once 
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UBattleComponent::EnemyAttack, Duration, false); // Starts the timer
	}
}

void UBattleComponent::EnemyAttack()
{
	int num = FMath::RandRange(1, 10); // Used for getting a random value for determining if the enemy has hit or missed
	
	if(num >= 1 && num <= 4) // The enemy has a 40% chance of hitting 
	{
		HealthComponent->Damage(10); // Does 10 damage if a hit is success full
		bEnemyHit = true; // The enemy has hit
	}
	else
	{
		bEnemyHit = false; // The enemy has missed
	}

	bIsPlayersTurn = true; // Sets the players turn
	DoOnce = 0; // Resets the count
}

