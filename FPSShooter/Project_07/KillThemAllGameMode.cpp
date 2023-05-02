// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

//checking end gamelogic
void AKillThemAllGameMode::PawnKilled(APawn* PawnKilled)
{
    if (PawnKilled != nullptr) {
        APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
        if (PlayerController) {
            EndGame(false);
        }
    }
    
    
    if (FoundWayOut) {
        EndGame(true);
    }
   /** 
    // for loop over ShooterAi in World use this for kill all enemy to end game
    for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld())) {
        if (!AIController->IsDead()) {
            return;
       }
    }
     EndGame(true);
   */
   
}

void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld())) {
        bool bIsPlayerController = Controller->IsPlayerController();
        bool bIsWinner = bIsPlayerController == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
  
}
