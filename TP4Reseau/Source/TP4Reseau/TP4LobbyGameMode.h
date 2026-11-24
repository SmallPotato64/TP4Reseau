// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Character.h"
#include "TP4LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TP4RESEAU_API ATP4LobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATP4LobbyGameMode();

	// Valide et applique le choix d'un héros demandé par un joueur (côté serveur)
	void RequestSelectHero(APlayerController* Requester, TSubclassOf<ACharacter> HeroClass);

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Liste des héros autorisés dans le lobby
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby")
	TArray<TSubclassOf<ACharacter>> AllowedHeroes;

private:
	bool bTravelTriggered = false;

	void CheckAllPlayersReady();
};
