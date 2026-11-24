// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4GameplayGameMode.h"
#include "TP4GameplayPlayerController.h"
#include "TP4ReseauPlayerState.h"
#include "GameFramework/Character.h"

ATP4GameplayGameMode::ATP4GameplayGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("ATP4GameplayGameMode: Constructing gamemode"));
	PlayerControllerClass = ATP4GameplayPlayerController::StaticClass();
	PlayerStateClass = ATP4ReseauPlayerState::StaticClass();
}

UClass* ATP4GameplayGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	UE_LOG(LogTemp, Warning, TEXT("ATP4GameplayGameMode: Getting default pawn class"));
	if (InController)
	{
		if (ATP4ReseauPlayerState* PS = InController->GetPlayerState<ATP4ReseauPlayerState>())
		{
			if (PS->SelectedHero != nullptr)
			{
				return PS->SelectedHero;
			}
		}
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}