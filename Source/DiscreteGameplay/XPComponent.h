// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XPComponent.generated.h"


class UWidgetComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISCRETEGAMEPLAY_API UXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXPComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		FText GetLevel(); // Gets the current xp level to show in the UI

	UFUNCTION()
		void AddXP(int XP); // Adds XP
		
	UFUNCTION(BlueprintCallable)
		float GetProgressBarXP(); // Gets XP value for progress bar
	
private:
	UPROPERTY()
		int LevelCount = 1; // Level count 

	UPROPERTY()
		int XPCount = 0; // XP count

	UPROPERTY()
		int XPLevelUp = 25; // Increaese each time there is a level up

	UPROPERTY()
		float ProgressBarXP = 0.0f; // XP bar value
};
