// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4GameplayGameMode.h"
#include "TP4GameplayPlayerController.h"
#include "TP4ReseauPlayerState.h"
#include "GameFramework/Character.h"

ATP4GameplayGameMode::ATP4GameplayGameMode()
{
	PlayerControllerClass = ATP4GameplayPlayerController::StaticClass();
	PlayerStateClass = ATP4ReseauPlayerState::StaticClass();
}

UClass* ATP4GameplayGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
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