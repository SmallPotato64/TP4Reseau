// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4LobbyPlayerController.h"
// #include "TP4LobbyGameMode.h"
#include "TP4LobbyGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ATP4LobbyPlayerController::ATP4LobbyPlayerController()
{
}

void ATP4LobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	bShowMouseCursor = true;
	SetIgnoreMoveInput(true);
	SetIgnoreLookInput(true);

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	if (LobbyWidgetClass && !LobbyWidgetInstance)
	{
		LobbyWidgetInstance = CreateWidget<UUserWidget>(this, LobbyWidgetClass);
		if (LobbyWidgetInstance)
		{
			LobbyWidgetInstance->AddToViewport();
			InputMode.SetWidgetToFocus(LobbyWidgetInstance->TakeWidget());
			SetInputMode(InputMode);
		}
	}
}

void ATP4LobbyPlayerController::Server_SelectHero_Implementation(TSubclassOf<ACharacter> HeroClass)
{
	// S'exécute uniquement sur le serveur
	if (!HasAuthority())
	{
		return;
	}

	if (ATP4LobbyGameMode* LobbyGM = GetWorld()->GetAuthGameMode<ATP4LobbyGameMode>())
	{
		LobbyGM->RequestSelectHero(this, HeroClass);
	}
}