// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP4ReseauGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ATP4ReseauGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ATP4ReseauGameMode();
};



