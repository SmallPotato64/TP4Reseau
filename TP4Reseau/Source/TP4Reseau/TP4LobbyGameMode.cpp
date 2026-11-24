// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4LobbyGameMode.h"
#include "TP4LobbyPlayerController.h"
#include "TP4ReseauPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "UObject/ConstructorHelpers.h"

ATP4LobbyGameMode::ATP4LobbyGameMode()
{
	bUseSeamlessTravel = true;

	PlayerControllerClass = ATP4LobbyPlayerController::StaticClass();
	PlayerStateClass = ATP4ReseauPlayerState::StaticClass();
	DefaultPawnClass = nullptr;
}

void ATP4LobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!HasAuthority())
	{
		return;
	}

	CheckAllPlayersReady();
}

void ATP4LobbyGameMode::RequestSelectHero(APlayerController* Requester, TSubclassOf<ACharacter> HeroClass)
{
	if (!HasAuthority() || bTravelTriggered || !Requester)
	{
		return;
	}

	// Validation serveur : le héros doit être non nul et faire partie de la liste autorisée
	if (!HeroClass || !AllowedHeroes.Contains(HeroClass))
	{
		return;
	}

	ATP4ReseauPlayerState* PS = Requester->GetPlayerState<ATP4ReseauPlayerState>();
	if (!PS)
	{
		return;
	}

	PS->SetSelectedHero(HeroClass);

	// Vérifie si les 2 joueurs sont présents et ont chacun choisi un héros
	CheckAllPlayersReady();
}

void ATP4LobbyGameMode::CheckAllPlayersReady()
{
	if (!HasAuthority() || bTravelTriggered || !GameState)
	{
		return;
	}

	// Exactement 2 joueurs connectés
	if (GameState->PlayerArray.Num() < 2)
	{
		return;
	}

	for (APlayerState* BasePS : GameState->PlayerArray)
	{
		ATP4ReseauPlayerState* PS = Cast<ATP4ReseauPlayerState>(BasePS);
		if (!PS || PS->SelectedHero == nullptr)
		{
			// Au moins un joueur n'a pas encore choisi son héros
			return;
		}
	}

	bTravelTriggered = true;

	UE_LOG(LogTemp, Warning, TEXT("LobbyGameMode: Launching Server Travel."));
	// Déclenche le Seamless Travel vers la carte Game
	GetWorld()->ServerTravel(TEXT("/Game/ThirdPerson/Levels/Game?listen"));
}