// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TP4MainMenuWidget.generated.h"

class UEditableTextBox;
class UButton;

UCLASS()
class TP4RESEAU_API UTP4MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> IPTextBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> HostButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinButton;

private:
	UFUNCTION()
	void OnHostClicked();

	UFUNCTION()
	void OnJoinClicked();
};
