// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Simple_shooterGameModeBase.h"
#include "KillThemAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AKillThemAllGameMode : public ASimple_shooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
	
};
