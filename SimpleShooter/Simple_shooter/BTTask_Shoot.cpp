// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Shooter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"


UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot the Player");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);
    AShooter* ControllerPawn =  Cast<AShooter>(OwnerComp.GetAIOwner()->GetPawn());
    if(!ControllerPawn){
        return EBTNodeResult::Failed;
    }
    APawn* PlayerPawn =  UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    float FireRange = ControllerPawn->Gun->GetMaxFireRange();
    if(PlayerPawn){
        float Distance =FVector::Dist(ControllerPawn->GetActorLocation(),PlayerPawn->GetActorLocation());
        if(Distance<= FireRange){
            UE_LOG(LogTemp,Warning,TEXT("Distance = %f"),Distance);
            ControllerPawn->Shoot();
            return EBTNodeResult::Succeeded;
        }
    }
   return EBTNodeResult::Failed;
}

//(X=-20.418560,Y=23.593176,Z=125.609955)
//(Pitch=0.266951,Yaw=0.047029,Roll=39.998287)
