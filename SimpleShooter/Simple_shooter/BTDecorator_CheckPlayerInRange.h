// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckPlayerInRange.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API UBTDecorator_CheckPlayerInRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckPlayerInRange();

	
};
