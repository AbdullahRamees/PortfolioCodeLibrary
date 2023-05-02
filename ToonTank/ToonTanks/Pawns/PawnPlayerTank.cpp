// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlayerTank.h"
#include "Kismet/GameplayStatics.h"

APawnPlayerTank::APawnPlayerTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

bool APawnPlayerTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}

void APawnPlayerTank::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);

	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}