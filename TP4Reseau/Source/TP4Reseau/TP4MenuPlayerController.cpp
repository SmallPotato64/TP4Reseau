// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4MenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ATP4MenuPlayerController::ATP4MenuPlayerController()
{
}

void ATP4MenuPlayerController::BeginPlay()
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

	if (MainMenuWidgetClass && !MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			InputMode.SetWidgetToFocus(MainMenuWidgetInstance->TakeWidget());
			SetInputMode(InputMode);
		}
	}
}