// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceActor.h"

#include "InventoryComponent.h"
#include "ResourceLabel.h"
#include "ResourceSpawnerActor.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseResourceActor::ABaseResourceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); // Creates the mesh in blueprints 
	
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget")); // Creates the widget in the blueprints
	WidgetComp->SetupAttachment(ActorMesh); // Attaches widget to the mesh

	// Setups the collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(ActorMesh);
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseResourceActor::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void ABaseResourceActor::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<ADiscreteGameplayGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); // Creates a reference to the game mode to access variables and function
}

// Called every frame
void ABaseResourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseResourceActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Gets player
	
	if(OtherActor == Player) // Checks if the overlapping actor is the player
	{
		UInventoryComponent* comp = Player->FindComponentByClass<UInventoryComponent>(); // Gets the component
		if(ResourceName == "Tree") 
		{
			GameModeRef->SpawnerActor->TreeCount--; // Removes tree
			comp->AddWood(); // Add wood to the inventory
			
		}
		else if(ResourceName == "Rock")
		{
			GameModeRef->SpawnerActor->RockCount--; // Removes Rock
			comp->AddStone(); // Add Stone
		}
		else if(ResourceName == "Iron Ore")
		{
			GameModeRef->SpawnerActor->IronOreCount--; // Removes Iron
			comp->AddIron(); // Add Iron
		}
		else if(ResourceName == "Gold Ore")
		{
			GameModeRef->SpawnerActor->GoldOreCount--; // Removes gold
			comp->AddGold();  // Add Gold
		}
		Destroy(); // Destroys this actor and removes it from the world
	}
}

