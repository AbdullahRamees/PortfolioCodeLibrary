// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_shoot.h"
#include "FPSCharater.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>


UBTTask_shoot::UBTTask_shoot()
{
	NodeName = TEXT("Shoot the Player");
}

EBTNodeResult::Type UBTTask_shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    //getting controlled pawn to verify gun
    AFPSCharater* ControllerPawn = Cast<AFPSCharater>(OwnerComp.GetAIOwner()->GetPawn());
    if (!ControllerPawn) {
        return EBTNodeResult::Failed;
    }
    //Checking shooting limit distance and shoot
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    float FireRange = ControllerPawn->GetMaxFireRange();
    if (PlayerPawn) {
        float Distance = FVector::Dist(ControllerPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
        if (Distance <= FireRange) {
            //UE_LOG(LogTemp, Warning, TEXT("Distance = %f"), Distance);
            ControllerPawn->Shoot();
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}
