// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTServices_PlayerLocationIfSeen::UBTServices_PlayerLocationIfSeen()
{
      NodeName = TEXT("Update Player If Seen ");
}

void UBTServices_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    //need to update player location if on site 
    AAIController* Control = OwnerComp.GetAIOwner();
    if(!Control){
        return;
    }
    APawn* PlayerPawn =  UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(!PlayerPawn){
        return;
    }
    if(Control->LineOfSightTo(PlayerPawn)){
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),PlayerPawn);
    }
    else{
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}

