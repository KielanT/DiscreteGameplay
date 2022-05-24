// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Health = MAX_HEALTH;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(HungerTimer, this, &UHealthComponent::Hunger, HungerDuration, true); // Starts the timer and loops through out the entire game
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(Health <= 0) // If the player dies show the game over screen
	{
		
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if(Widget != nullptr)
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			Widget->AddToViewport();
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void UHealthComponent::Damage(int Damage)
{
	Health -= Damage; // Removes health depending on the damage
	float difference = ProgressBarHealth - ((float)Health / float(MAX_HEALTH)); // Calculates the health to be removed from the progress bar
	ProgressBarHealth -= difference; // Removes the health from the progress bar
}

float UHealthComponent::GetProgressBarHealth()
{
	return ProgressBarHealth; // Gets the value for UI
}

void UHealthComponent::RefillHealth(int health)
{
	// Increases the health
	Health += health;
	float difference = ProgressBarHealth - ((float)Health / float(MAX_HEALTH)); // Calculates the difference to be added
	ProgressBarHealth += difference; // Add back to the the progress bar
}

void UHealthComponent::Hunger()
{
	if(Health > 20 && !bBattleMode) // Only does the hunger if not in battle and the health is bigger than 20
	{
		HungerDamage = FMath::RandRange(1, 5);
		Damage(HungerDamage);
	}
}

