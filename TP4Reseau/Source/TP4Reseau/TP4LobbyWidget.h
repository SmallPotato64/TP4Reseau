// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "TP4LobbyWidget.generated.h"

class UButton;
class UTextBlock;
class ATP4ReseauPlayerState;

UCLASS()
class TP4RESEAU_API UTP4LobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Classes des deux héros associées aux boutons (chargées en C++ ou assignables)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby")
	TSubclassOf<ACharacter> MannyHeroClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby")
	TSubclassOf<ACharacter> QuinnHeroClass;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MannyButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuinnButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Player1NameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Player1HeroText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Player2NameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Player2HeroText;

private:
	UPROPERTY()
	TArray<TObjectPtr<ATP4ReseauPlayerState>> ObservedPlayerStates;

	FTimerHandle SyncPlayersTimerHandle;

	UFUNCTION()
	void OnMannyClicked();

	UFUNCTION()
	void OnQuinnClicked();

	UFUNCTION()
	void HandlePlayerStateUpdated(ATP4ReseauPlayerState* UpdatedPS);

	void SyncPlayerSubscriptionsAndUI();
	FString FormatHeroName(TSubclassOf<ACharacter> HeroClass) const;
};
