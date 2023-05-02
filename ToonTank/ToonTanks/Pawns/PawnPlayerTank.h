// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "PawnPlayerTank.generated.h"


/**
 * 
 */

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnPlayerTank : public APawnTank
{
	GENERATED_BODY()
	

public:

	APawnPlayerTank();
	virtual void HandleDestruction() override;
	bool GetIsPlayerAlive();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	bool bIsPlayerAlive = true;
};
