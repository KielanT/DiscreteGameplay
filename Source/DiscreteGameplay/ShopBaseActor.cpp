// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopBaseActor.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShopBaseActor::AShopBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); // Creates mesh
	
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget")); // Creates widget
	WidgetComp->SetupAttachment(ActorMesh);
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box")); // Creates collision box
	CollisionBox->SetupAttachment(ActorMesh);
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetBoxExtent(FVector(70.0f, 70.0f, 70.0f));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShopBaseActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AShopBaseActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController(); // Gets player controller
	
}

// Called every frame
void AShopBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShopBaseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Gets player

	if(OtherActor == Player) // Checks if the colliding actor is the player and shows shop UI
	{
		Widget = CreateWidget<UUserWidget>(GetWorld(), ShopWidgetClass);
		if(Widget != nullptr)
		{
			Widget->AddToViewport();
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}
	}
}

