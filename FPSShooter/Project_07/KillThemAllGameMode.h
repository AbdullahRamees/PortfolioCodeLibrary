// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KillThemAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_07_API AKillThemAllGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	 void PawnKilled(APawn* PawnKilled);

	 UPROPERTY(EditAnywhere)
	 bool FoundWayOut;

	void EndGame(bool bIsPlayerWinner);
};
