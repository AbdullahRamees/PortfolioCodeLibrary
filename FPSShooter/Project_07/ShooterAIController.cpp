// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPSCharater.h"

void AShooterAIController::BeginPlay()
{
    //runing ai behaviour tree
    Super::BeginPlay();
    if (AIBehavior) {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    //geting shooter Death condition for AI
   AFPSCharater* ControlledCharactor = Cast<AFPSCharater>(GetPawn());
    if (ControlledCharactor) {
        return ControlledCharactor->IsDead();
    }

    return true;
}
