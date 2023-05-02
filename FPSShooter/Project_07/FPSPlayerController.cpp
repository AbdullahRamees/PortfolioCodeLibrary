// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AFPSPlayerController::BeginPlay()
{
    Super::BeginPlay();
    //initiate hud
    HUDWidget = CreateWidget(this, HUDScreenClass);
    if (HUDWidget) {
        HUDWidget->AddToViewport();
        FInputModeGameOnly();
    }
}

void AFPSPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    if (HUDWidget) {
        HUDWidget->RemoveFromViewport();
    }

    //showing endgame widgets
    if (bIsWinner) {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen) {
            WinScreen->AddToViewport();
            DisableInput(this);
            FInputModeUIOnly();
        }
    }
    else {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

        if (LoseScreen) {
            LoseScreen->AddToViewport();
            DisableInput(this);
            FInputModeUIOnly();
        }
    }


    GetWorldTimerManager().SetTimer(
        RestartTimer,
        this,
        &APlayerController::RestartLevel,
        RestartDelay
    );
    
}

