// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4GameplayPlayerController.h"

void ATP4GameplayPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalPlayerController())
	{
		return;
	}

	bShowMouseCursor = false;
	SetIgnoreMoveInput(false);
	SetIgnoreLookInput(false);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}