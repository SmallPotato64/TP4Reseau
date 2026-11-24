// Fill out your copyright notice in the Description page of Project Settings.


#include "TP4MainMenuWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void UTP4MainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IPTextBox)
	{
		IPTextBox->SetText(FText::FromString(TEXT("127.0.0.1:7777")));
	}

	if (HostButton)
	{
		HostButton->OnClicked.RemoveDynamic(this, &UTP4MainMenuWidget::OnHostClicked);
		HostButton->OnClicked.AddDynamic(this, &UTP4MainMenuWidget::OnHostClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.RemoveDynamic(this, &UTP4MainMenuWidget::OnJoinClicked);
		JoinButton->OnClicked.AddDynamic(this, &UTP4MainMenuWidget::OnJoinClicked);
	}
}

void UTP4MainMenuWidget::OnHostClicked()
{
	// Ouvre la carte Lobby en tant que Listen Server
	UGameplayStatics::OpenLevel(this, FName(TEXT("Lobby")), true, TEXT("listen"));
}

void UTP4MainMenuWidget::OnJoinClicked()
{
	if (!IPTextBox)
	{
		return;
	}

	const FString Address = IPTextBox->GetText().ToString().TrimStartAndEnd();
	if (Address.IsEmpty())
	{
		return;
	}

	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}