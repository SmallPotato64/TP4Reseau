// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4ReseauPlayerState.h"
#include "Net/UnrealNetwork.h"

ATP4ReseauPlayerState::ATP4ReseauPlayerState()
{
	SelectedHero = nullptr;
}

void ATP4ReseauPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATP4ReseauPlayerState, SelectedHero);
}

void ATP4ReseauPlayerState::SetSelectedHero(TSubclassOf<ACharacter> NewHero)
{
	if (!HasAuthority())
	{
		return;
	}

	if (SelectedHero != NewHero)
	{
		SelectedHero = NewHero;

		// Sur le serveur, OnRep ne se déclenche pas automatiquement pour la modification locale, on déclenche donc l'événement manuellement ici
		OnSelectedHeroChanged.Broadcast(this);
	}
}

void ATP4ReseauPlayerState::OnRep_SelectedHero()
{
	OnSelectedHeroChanged.Broadcast(this);
}

void ATP4ReseauPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	ATP4ReseauPlayerState* NewPS = Cast<ATP4ReseauPlayerState>(PlayerState);
	if (NewPS)
	{
		NewPS->SelectedHero = SelectedHero;
	}
}