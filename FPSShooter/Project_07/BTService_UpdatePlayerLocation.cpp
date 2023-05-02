// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPSCharater.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = TEXT("Update Player If Seen ");
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
   
    //need to update player location if on site 
    //Finding AI Controller
    AAIController* Control = OwnerComp.GetAIOwner();
    if (!Control) {
        return;
    }
    //GETING PLAYER PAWN
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    AFPSCharater* PlayerCharacter = Cast<AFPSCharater>(PlayerPawn);
    if (!PlayerPawn) {
        return;
    }
    //checking line of site and add to blackBoard 
    if (Control->LineOfSightTo(PlayerPawn) && PlayerCharacter->IsDead() == false) {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else {
        //Clearing if not seen
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
