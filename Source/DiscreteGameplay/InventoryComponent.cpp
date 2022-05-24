// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"


#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Gets player
	XPComp = Player->FindComponentByClass<UXPComponent>();
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UInventoryComponent::AddWood()
{
	if(WoodCount <= MAX_RESOURCE_SIZE) // Checks if the count is smaller or equal to max resource
	{
		int num = FMath::RandRange(1, 4); // Gets a random number of what the wood should increase by
		WoodCount += num; // Increases the wood count
		XPComp->AddXP(FMath::RandRange(1, 3)); // Increases the XP
	}
}

void UInventoryComponent::AddStone()
{
	if(StoneCount <= MAX_RESOURCE_SIZE)
	{
		int num = FMath::RandRange(1, 3);
		StoneCount += num;
		XPComp->AddXP(FMath::RandRange(1, 3));
	}
}

void UInventoryComponent::AddIron()
{
	if(IronCount <= MAX_RESOURCE_SIZE)
	{
		int num = FMath::RandRange(1, 2);
		IronCount += num;
		XPComp->AddXP(FMath::RandRange(1, 3));
	}
}

void UInventoryComponent::AddGold()
{
	if(GoldCount <= MAX_RESOURCE_SIZE)
	{
		GoldCount++;
		XPComp->AddXP(FMath::RandRange(1, 5));
	}
}

FText UInventoryComponent::GetWoodCount()
{
	return FText::FromString(FString::FromInt(WoodCount)); // Gets the Count for the UI
}

FText UInventoryComponent::GetStoneCount()
{
	return FText::FromString(FString::FromInt(StoneCount));
}

FText UInventoryComponent::GetIronCount()
{
	return FText::FromString(FString::FromInt(IronCount));
}

FText UInventoryComponent::GetGoldCount()
{
	return FText::FromString(FString::FromInt(GoldCount));
}

FText UInventoryComponent::GetStoneSwordCount()
{
	return FText::FromString(FString::FromInt(StoneSwordCount));
}

void UInventoryComponent::BuyStoneSword()
{
	if(GoldCount >= 2) // Can only buy a stone sword if there is 2 or more gold
	{
		StoneSwordCount++;
		GoldCount -= 2;
	}
}

bool UInventoryComponent::bCheckEnoughGoldForStoneSword()
{
	if(GoldCount >= 2) // Checks if there is enough gold for the sword 
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UInventoryComponent::bCheckForStoneSword()
{
	if(StoneSwordCount >= 1) // Checks if there is a stone sword (Can only battle if there is a stone sword in the inventory)
		return true;
	else
		return false;
}

void UInventoryComponent::CraftStoneSword() 
{
	if (WoodCount >= 1 && StoneCount >= 2) // Only crafts a sword if there is enough wood and stone
	{
		StoneSwordCount++;
		WoodCount -= 1;
		StoneCount -= 2;
	}
}

