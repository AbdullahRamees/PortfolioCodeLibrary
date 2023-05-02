// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"




UBTTask_ClearBlackBoardKey::UBTTask_ClearBlackBoardKey()
{
    NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackBoardKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    UBlackboardComponent* BlackBoardCom =OwnerComp.GetBlackboardComponent();
    BlackBoardCom->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}
