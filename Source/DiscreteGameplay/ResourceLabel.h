// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ResourceLabel.generated.h"

/**
 * 
 */
UCLASS()
class DISCRETEGAMEPLAY_API UResourceLabel : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* Label;
	
protected:
	virtual bool Initialize() override;
};
