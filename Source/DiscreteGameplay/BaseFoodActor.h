// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseFoodActor.generated.h"

class ADiscreteGameplayGameModeBase;
class UBoxComponent;
class UWidgetComponent;
UCLASS()
class DISCRETEGAMEPLAY_API ABaseFoodActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseFoodActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ActorMesh; // Used for adding a mesh in blueprints

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetComponent* WidgetComp; // Used for adding a label widget in blueprint

private:
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox; // Collision box for detecting when the playing picks it up
	

	UPROPERTY(EditAnywhere)
	ADiscreteGameplayGameModeBase* GameModeRef; // Used to create the reference to game mode
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Used to check when collision box is entered
};
