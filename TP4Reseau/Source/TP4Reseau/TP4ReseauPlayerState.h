// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Character.h"
#include "TP4ReseauPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedHeroChanged, ATP4ReseauPlayerState*, PlayerState);

UCLASS()
class TP4RESEAU_API ATP4ReseauPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATP4ReseauPlayerState();

	// Héros choisi dans le lobby (répliqué vers tous les clients)
	UPROPERTY(ReplicatedUsing = OnRep_SelectedHero, BlueprintReadOnly, Category = "Lobby")
	TSubclassOf<ACharacter> SelectedHero;

	// Événement déclenché quand le héros change (pour mettre à jour le widget sans Tick)
	UPROPERTY(BlueprintAssignable, Category = "Lobby")
	FOnSelectedHeroChanged OnSelectedHeroChanged;

	// Appelé uniquement côté serveur pour définir/valider le héros choisi
	void SetSelectedHero(TSubclassOf<ACharacter> NewHero);

	// Obligatoire pour déclarer les propriétés répliquées
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_SelectedHero();

	// Persistance des données lors d'un Seamless Travel (appelé côté serveur)
	virtual void CopyProperties(APlayerState* PlayerState) override;
};
