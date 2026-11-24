// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "TP4LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TP4RESEAU_API ATP4LobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATP4LobbyPlayerController();

	// RPC appelée depuis le widget du client local vers le serveur
	UFUNCTION(Server, Reliable)
	void Server_SelectHero(TSubclassOf<ACharacter> HeroClass);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> LobbyWidgetInstance;
};
