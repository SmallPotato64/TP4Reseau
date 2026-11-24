// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP4ReseauPlayerController.h"
#include "TP4GameplayPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TP4RESEAU_API ATP4GameplayPlayerController : public ATP4ReseauPlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
