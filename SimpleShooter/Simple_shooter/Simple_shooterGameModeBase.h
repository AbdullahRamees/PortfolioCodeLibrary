// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Simple_shooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API ASimple_shooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);	
};
