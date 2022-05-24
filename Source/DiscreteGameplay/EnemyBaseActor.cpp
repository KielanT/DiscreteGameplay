// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseActor.h"

#include "BattleComponent.h"
#include "DiscreteGameplayGameModeBase.h"
#include "HealthComponent.h"
#include "ResourceSpawnerActor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBaseActor::AEnemyBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); // Creates mesh
	
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget")); // Creates widget
	WidgetComp->SetupAttachment(ActorMesh);

	// Sets up the collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(ActorMesh);
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBaseActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AEnemyBaseActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController(); // Gets the player controller
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Gets player
	BattleComponent = Player->FindComponentByClass<UBattleComponent>(); // Gets the component

	GameModeRef = Cast<ADiscreteGameplayGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); // Gets the game mode
}

// Called every frame
void AEnemyBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(BattleComponent->GetEnemyHealthBar() <= 0.0f) // Gets the health bar to check if the enemy has been killed
	{
		GameModeRef->SpawnerActor->EnemyCount--; // only needed for multiple enemeies for spawning a new wave (currently not working)
		Destroy(); // Destroys current actor
	}
}

void AEnemyBaseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Gets player
	
	if(OtherActor == Player) // Checks if the player is the colliding actor
	{
		Widget = CreateWidget<UUserWidget>(GetWorld(), EnemyWidgetClass); // Creates the enemy ui for a battle
		if(Widget != nullptr) // Checks if its been created
		{
			Widget->AddToViewport(); // Shows the widget
			PlayerController->SetInputMode(FInputModeUIOnly()); // Changes input mode to ui
			PlayerController->bShowMouseCursor = true; // Shows the mouse
			UHealthComponent* comp = Player->FindComponentByClass<UHealthComponent>(); // Health component 
			comp->SetBattleMode(true); // Sets battle mode so that the player does not lose health from hunger in battle
		}
	}
	
}

