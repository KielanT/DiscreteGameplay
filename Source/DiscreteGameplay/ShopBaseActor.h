// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShopBaseActor.generated.h"

class UBoxComponent;
class UWidgetComponent;
UCLASS()
class DISCRETEGAMEPLAY_API AShopBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShopBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> ShopWidgetClass;

	UPROPERTY()
		UUserWidget* Widget;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ActorMesh;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* WidgetComp;

	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Used to check when collision box is entered

	UPROPERTY()
		APlayerController* PlayerController; 
};
