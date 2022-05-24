// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFoodActor.h"

#include "BaseResourceActor.h"
#include "HealthComponent.h"
#include "ResourceSpawnerActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseFoodActor::ABaseFoodActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); // Creates the mesh
	
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget")); // Creates the widget
	WidgetComp->SetupAttachment(ActorMesh); // Attaches the widget to the mesh

	// Setup the collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(ActorMesh);
	CollisionBox->SetCollisionProfileName("Trigger"); // Sets the collision to a trigger
	CollisionBox->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseFoodActor::OnOverlapBegin); // Sets the function for the collision
}

// Called when the game starts or when spawned
void ABaseFoodActor::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<ADiscreteGameplayGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));  // Used to get the spawner actor 
}

// Called every frame
void ABaseFoodActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseFoodActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Gets player
	
	if(OtherActor == Player) // Checks if the overlapping actor is the player
	{
		UHealthComponent* comp = Player->FindComponentByClass<UHealthComponent>(); // Gets the component 
		GameModeRef->SpawnerActor->FoodCount--; // Removes a piece of food from the count
		int Health = FMath::RandRange(1, 5); // Chooses a random amount to refill the health by
		comp->RefillHealth(Health); // Refills the Health
		Destroy(); // Destroys this object to remove from the world
	}
}

