// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTServices_PlayerLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API UBTServices_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTServices_PlayerLocationIfSeen();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
