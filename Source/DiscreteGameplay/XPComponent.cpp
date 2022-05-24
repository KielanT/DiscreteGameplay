// Fill out your copyright notice in the Description page of Project Settings.


#include "XPComponent.h"

#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UXPComponent::UXPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UXPComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UXPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Updates the XP values if the bar is full
	if(ProgressBarXP >= 1.0f)
	{
		LevelCount++;
		XPLevelUp += 25;
		XPCount = 0;
		ProgressBarXP = 0.0f;
	}
}

FText UXPComponent::GetLevel()
{
	return FText::FromString(FString::FromInt(LevelCount)); // Gets the count for UI
}


void UXPComponent::AddXP(int XP)
{
	// Adds XP and then sets it to the progress bar
	XPCount += XP; 
	float increaseXP = float(XPCount) / float(XPLevelUp);
	ProgressBarXP += increaseXP;
}

float UXPComponent::GetProgressBarXP()
{
	return ProgressBarXP; // Return the progress bar value
}

