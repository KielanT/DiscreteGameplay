// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealth.h"

// Sets default values for this component's properties
UEnemyHealth::UEnemyHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyHealth::Damage(int Damage)
{
	Health -= Damage; // Removes the health when damaged
	float difference = ProgressBarHealth - ((float)Health / float(MAX_HEALTH)); // Calculates the differences
	ProgressBarHealth -= difference; // Sets the progress bar
}

float UEnemyHealth::GetProgressBarHealth()
{
	return ProgressBarHealth; // Used for getting the progress bar value for the UI
}

