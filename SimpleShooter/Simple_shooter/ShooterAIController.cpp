// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Shooter.h"


void AShooterAIController::BeginPlay()
{   
    Super::BeginPlay();  
    if(AIBehavior){
        RunBehaviorTree(AIBehavior);  
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooter* ControlledCharactor = Cast<AShooter>(GetPawn());
    if(ControlledCharactor){
        return ControlledCharactor->IsDead();
    }

    return true;
}
