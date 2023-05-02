// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillThemAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    if(PawnKilled != nullptr){  
     APlayerController* PlayerController =  Cast<APlayerController>(PawnKilled->GetController());
        if(PlayerController){
           EndGame(false);
        }
    }
    //for loor over ShooterAi in World
    for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld())){
        if(!AIController->IsDead()){
            return;
        }
    }
    EndGame(true);
}

void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner)
{   
    for(AController* Controller :TActorRange<AController>(GetWorld())){
       bool bIsPlayerController =  Controller->IsPlayerController();
        bool bIsWinner = bIsPlayerController == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
    }
    
}
