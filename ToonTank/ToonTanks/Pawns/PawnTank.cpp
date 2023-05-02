// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "../Components/TankMovementComponent.h"


APawnTank::APawnTank()
{
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(TEXT("Movement Component"));
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	FVector TankLocation = GetActorLocation();

	//TODO: Fix weird bug
	SetActorLocation(FVector(TankLocation.X, TankLocation.Y, 89.0f));
}

