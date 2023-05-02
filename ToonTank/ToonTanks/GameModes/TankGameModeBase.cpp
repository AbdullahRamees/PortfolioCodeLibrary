// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "../Pawns/PawnPlayerTank.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

int32 ATankGameModeBase::GetEnemyCount()
{
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnBase::StaticClass(), EnemyActors);
	return EnemyActors.Num() - 1;
}

void ATankGameModeBase::HandleGameStart()
{
	TargetEnemies = GetEnemyCount();
	PlayerTank = Cast<APawnPlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (PlayerTank == DeadActor)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnBase* DestroyedTurret = Cast<APawnBase> (DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		TargetEnemies--;
		if (TargetEnemies <= 0)
		{
			HandleGameOver(true);
		}
	}
}

int ATankGameModeBase::GetTargetEnemies() const
{
	return TargetEnemies;
}


