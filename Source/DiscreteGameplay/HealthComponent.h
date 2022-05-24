// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISCRETEGAMEPLAY_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void Damage(int Damage); // Function for damaging the player

	UFUNCTION(BlueprintCallable)
			float GetProgressBarHealth(); // Gets the progress bar value for the UI

	UFUNCTION()
		void RefillHealth(int health); // Refills the health bar when food is picked up

	UFUNCTION(BlueprintCallable)
		void SetBattleMode(bool mode) { bBattleMode = mode; } // Sets the battle mode to stop the hunger 
	
	
private:

	UFUNCTION()
		void Hunger(); // Function for effecting hunger
	
	UPROPERTY()
		int Health; 
	
	const int MAX_HEALTH = 100;

	UPROPERTY()
		float ProgressBarHealth = 1.0f;

	UPROPERTY()
		int HungerDamage;

	UPROPERTY()
		FTimerHandle HungerTimer;
	
	UPROPERTY()
		float HungerDuration = 5.0f;

	UPROPERTY()
		bool bBattleMode = false;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WidgetClass;
};
