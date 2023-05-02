// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_07_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDScreenClass;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 2.f;

	FTimerHandle RestartTimer;

	UPROPERTY(VisibleAnywhere)
		UUserWidget* HUDWidget;

	
};
