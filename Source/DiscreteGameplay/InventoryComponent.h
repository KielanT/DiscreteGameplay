// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XPComponent.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISCRETEGAMEPLAY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/******      Functions for adding resources       ********/
	UFUNCTION()
		void AddWood();

	UFUNCTION()
		void AddStone();

	UFUNCTION()
		void AddIron();

	UFUNCTION()
		void AddGold();

	/******      Functions for Crafting       ********/
	UFUNCTION(BlueprintCallable)
		void CraftStoneSword();

	/******      Functions for Getting the resources count       ********/
	UFUNCTION(BlueprintCallable)
		FText GetWoodCount();

	UFUNCTION(BlueprintCallable)
		FText GetStoneCount();

	UFUNCTION(BlueprintCallable)
		FText GetIronCount();

	UFUNCTION(BlueprintCallable)
		FText GetGoldCount();

	UFUNCTION(BlueprintCallable)
		FText GetStoneSwordCount();

	/******      Functions for buying resources       ********/
	UFUNCTION(BlueprintCallable)
		void BuyStoneSword();

	/******      Functions for checking resource count       ********/
	UFUNCTION(BlueprintCallable)
	bool bCheckEnoughGoldForStoneSword();

	UFUNCTION(BlueprintCallable)
	bool bCheckForStoneSword();
	
private:
	/******      Variables for getting resources the count and increasing the count       ********/
	UPROPERTY()
		int WoodCount = 0;

	UPROPERTY()
		int StoneCount = 0;

	UPROPERTY()
		int IronCount = 0;

	UPROPERTY()
		int GoldCount = 0;

	UPROPERTY()
		int StoneSwordCount = 0;


	const int MAX_RESOURCE_SIZE = 20; // Max size of each resource that can be stored

	UPROPERTY()
		APawn* Player; // Stores the player pawn

	UPROPERTY()
		UXPComponent* XPComp; // Stores the xp component
	
};
