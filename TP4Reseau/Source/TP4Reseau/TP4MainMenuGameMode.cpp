// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4MainMenuGameMode.h"
#include "TP4MenuPlayerController.h"

ATP4MainMenuGameMode::ATP4MainMenuGameMode()
{
	PlayerControllerClass = ATP4MenuPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}