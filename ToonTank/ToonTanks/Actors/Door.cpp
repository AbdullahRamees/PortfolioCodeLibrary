// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Engine/World.h"
#include "../GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameMode = Cast<ATankGameModeBase>(GetWorld()->GetAuthGameMode());
	ClosedLocation = GetActorLocation();
	OpenLocation = FVector(ClosedLocation.X, ClosedLocation.Y, ClosedLocation.Z - DoorOffset);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnemyNumber = CurrentGameMode->GetTargetEnemies();

	if (EnemyThreshold == EnemyNumber)
	{
		IsOpen = true;
	}
}

