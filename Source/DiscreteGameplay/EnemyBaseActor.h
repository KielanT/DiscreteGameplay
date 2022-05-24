// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyBaseActor.generated.h"

class ADiscreteGameplayGameModeBase;
class UWidgetComponent;
class UBoxComponent;
UCLASS()
class DISCRETEGAMEPLAY_API AEnemyBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> EnemyWidgetClass;

	UPROPERTY()
		UUserWidget* Widget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ActorMesh; // Creates Mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetComponent* WidgetComp; // Creates widget

private:
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox; // Creates collision box

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Used to check when collision box is entered

	UPROPERTY()
		APlayerController* PlayerController;  // Creates player controller

	UPROPERTY()
		UBattleComponent* BattleComponent; // Creates the battle component

	UPROPERTY(EditAnywhere)
		ADiscreteGameplayGameModeBase* GameModeRef; // Used to create the reference to game mode
};
