// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "../Pawns/PawnPlayerTank.h"
#include "../Pawns/PawnBase.h"
#include "../Components/AimingComponent.h"
#include "../Components/TankMovementComponent.h"
#include "Engine/EngineTypes.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<APawnPlayerTank> (GetWorld()->GetFirstPlayerController()->GetPawn());
	ControlledTank = Cast<APawnBase>(GetPawn());

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATankAIController::CheckFireCondition, ControlledTank->GetAimingComponent()->GetFireRate(), true);
	auto MovementComponent = ControlledTank->FindComponentByClass<UTankMovementComponent>();
	if (MovementComponent)
	{
		HasMovementComponent = true;
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	//If the player is either dead, do nothing
	if (!PlayerTank)
	{
		return;
	}
	//Check if the player was seen
	if (ReturnDistanceToPlayer() <= ControlledTank->GetCombatRange())
	{
		HasSeenPlayer = true;
	}
	//Chase player
	if (HasSeenPlayer)
	{
		ControlledTank->GetAimingComponent()->RotateTurret(PlayerTank->GetActorLocation());
		if (HasMovementComponent)
		{
			
			MoveToActor(PlayerTank, ControlledTank->GetAcceptanceRadius());
		}
	}
}

float ATankAIController::ReturnDistanceToPlayer() const
{
	if (!PlayerTank)
	{
		return 0.0f;
	}
	return FVector::Dist(PlayerTank->GetActorLocation(), ControlledTank->GetActorLocation());
}

void ATankAIController::CheckFireCondition()
{
	if (!PlayerTank || !PlayerTank->GetIsPlayerAlive())
	{
		return;
	}

	if (ReturnDistanceToPlayer() <= ControlledTank->GetAimingComponent()->GetFireRange())
	{
		ControlledTank->GetAimingComponent()->Fire();
	}
}

