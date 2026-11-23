// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TP4MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TP4RESEAU_API ATP4MenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATP4MenuPlayerController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenuWidgetInstance;
};
