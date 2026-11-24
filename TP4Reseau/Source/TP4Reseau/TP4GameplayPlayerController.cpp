// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4GameplayPlayerController.h"

void ATP4GameplayPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("ATP4GameplayPlayerController: Begin play"));
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