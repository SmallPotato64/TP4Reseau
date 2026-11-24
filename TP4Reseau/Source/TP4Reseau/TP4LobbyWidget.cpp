// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4LobbyWidget.h"
#include "TP4LobbyPlayerController.h"
#include "TP4ReseauPlayerState.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void UTP4LobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MannyButton)
	{
		MannyButton->OnClicked.RemoveDynamic(this, &UTP4LobbyWidget::OnMannyClicked);
		MannyButton->OnClicked.AddDynamic(this, &UTP4LobbyWidget::OnMannyClicked);
	}

	if (QuinnButton)
	{
		QuinnButton->OnClicked.RemoveDynamic(this, &UTP4LobbyWidget::OnQuinnClicked);
		QuinnButton->OnClicked.AddDynamic(this, &UTP4LobbyWidget::OnQuinnClicked);
	}

	SyncPlayerSubscriptionsAndUI();

	// Vérification légère tant que les 2 joueurs ne sont pas encore tous abonnés (pas de Tick)
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			SyncPlayersTimerHandle,
			this,
			&UTP4LobbyWidget::SyncPlayerSubscriptionsAndUI,
			0.25f,
			true
		);
	}
}

void UTP4LobbyWidget::NativeDestruct()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(SyncPlayersTimerHandle);
	}

	for (ATP4ReseauPlayerState* PS : ObservedPlayerStates)
	{
		if (PS)
		{
			PS->OnSelectedHeroChanged.RemoveDynamic(this, &UTP4LobbyWidget::HandlePlayerStateUpdated);
		}
	}
	ObservedPlayerStates.Empty();

	Super::NativeDestruct();
}

void UTP4LobbyWidget::OnMannyClicked()
{
	if (!MannyHeroClass)
	{
		return;
	}

	if (ATP4LobbyPlayerController* LobbyPC = Cast<ATP4LobbyPlayerController>(GetOwningPlayer()))
	{
		LobbyPC->Server_SelectHero(MannyHeroClass);
	}
}

void UTP4LobbyWidget::OnQuinnClicked()
{
	if (!QuinnHeroClass)
	{
		return;
	}

	if (ATP4LobbyPlayerController* LobbyPC = Cast<ATP4LobbyPlayerController>(GetOwningPlayer()))
	{
		LobbyPC->Server_SelectHero(QuinnHeroClass);
	}
}

void UTP4LobbyWidget::HandlePlayerStateUpdated(ATP4ReseauPlayerState* UpdatedPS)
{
	SyncPlayerSubscriptionsAndUI();
}

void UTP4LobbyWidget::SyncPlayerSubscriptionsAndUI()
{
	AGameStateBase* GS = GetWorld() ? GetWorld()->GetGameState() : nullptr;
	if (!GS)
	{
		return;
	}

	// Abonnement aux nouveaux PlayerState présents dans PlayerArray
	for (APlayerState* BasePS : GS->PlayerArray)
	{
		ATP4ReseauPlayerState* PS = Cast<ATP4ReseauPlayerState>(BasePS);
		if (PS && !ObservedPlayerStates.Contains(PS))
		{
			PS->OnSelectedHeroChanged.AddUniqueDynamic(this, &UTP4LobbyWidget::HandlePlayerStateUpdated);
			ObservedPlayerStates.Add(PS);
		}
	}

	// Mise à jour de l'affichage pour le Joueur 1 et le Joueur 2
	const int32 NumPlayers = GS->PlayerArray.Num();

	if (Player1NameText && Player1HeroText)
	{
		if (NumPlayers >= 1 && GS->PlayerArray[0])
		{
			APlayerState* P1 = GS->PlayerArray[0];
			ATP4ReseauPlayerState* PS1 = Cast<ATP4ReseauPlayerState>(P1);
			Player1NameText->SetText(FText::FromString(P1->GetPlayerName()));
			Player1HeroText->SetText(FText::FromString(FormatHeroName(PS1 ? PS1->SelectedHero : nullptr)));
		}
		else
		{
			Player1NameText->SetText(FText::FromString(TEXT("Joueur 1")));
			Player1HeroText->SetText(FText::FromString(TEXT("En attente")));
		}
	}

	if (Player2NameText && Player2HeroText)
	{
		if (NumPlayers >= 2 && GS->PlayerArray[1])
		{
			APlayerState* P2 = GS->PlayerArray[1];
			ATP4ReseauPlayerState* PS2 = Cast<ATP4ReseauPlayerState>(P2);
			Player2NameText->SetText(FText::FromString(P2->GetPlayerName()));
			Player2HeroText->SetText(FText::FromString(FormatHeroName(PS2 ? PS2->SelectedHero : nullptr)));
		}
		else
		{
			Player2NameText->SetText(FText::FromString(TEXT("Joueur 2")));
			Player2HeroText->SetText(FText::FromString(TEXT("En attente")));
		}
	}

	// Dès que les 2 joueurs sont présents et abonnés, plus besoin du timer d'attente
	if (ObservedPlayerStates.Num() >= 2 && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(SyncPlayersTimerHandle);
	}
}

FString UTP4LobbyWidget::FormatHeroName(TSubclassOf<ACharacter> HeroClass) const
{
	if (!HeroClass)
	{
		return TEXT("En attente");
	}

	FString ClassName = HeroClass->GetName();
	ClassName.RemoveFromStart(TEXT("BP_Hero"));
	ClassName.RemoveFromEnd(TEXT("_C"));
	return ClassName.IsEmpty() ? TEXT("Héros sélectionné") : ClassName;
}