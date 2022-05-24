// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyHealth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISCRETEGAMEPLAY_API UEnemyHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void Damage(int Damage);

	UFUNCTION(BlueprintCallable)
			float GetProgressBarHealth();
	
private:
	const int MAX_HEALTH = 80; // Constant max health for enemeies
	
	UPROPERTY()
		int Health = MAX_HEALTH; // Sets health to the max health

	UPROPERTY()
	float ProgressBarHealth = 1.0f; // Variable for the progress bar value
};
