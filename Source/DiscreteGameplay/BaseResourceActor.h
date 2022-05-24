// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiscreteGameplayGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "BaseResourceActor.generated.h"


UCLASS()
class DISCRETEGAMEPLAY_API ABaseResourceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseResourceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ActorMesh; // Creates mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetComponent* WidgetComp; // Creates widget

private:
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox; // Creates collision box
	
	UPROPERTY(EditAnywhere)
		FString ResourceName; // Used for storing the resource name and checking the resource type

	UPROPERTY(EditAnywhere)
		ADiscreteGameplayGameModeBase* GameModeRef; // Used to create the reference to game mode
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Used to check when collision box is entered
	
};
