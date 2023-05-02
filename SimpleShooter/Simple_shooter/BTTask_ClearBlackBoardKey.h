// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackBoardKey.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API UBTTask_ClearBlackBoardKey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ClearBlackBoardKey();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
