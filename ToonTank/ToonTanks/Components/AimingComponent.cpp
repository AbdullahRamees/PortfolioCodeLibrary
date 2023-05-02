// Fill out your copyright notice in the Description page of Project Settings.


#include "AimingComponent.h"
#include "../Actors/ProjectileBase.h"
#include "../Pawns/PawnBase.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<APawnBase>(GetOwner());
	// ...
	TurretMesh = OwnerPawn->GetTurretMesh();

}

void UAimingComponent::RotateTurret(FVector LookAtTarget)
{
	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FRotator TurretRotation = FVector(LookAtTargetCleaned - TurretMesh->GetComponentLocation()).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void UAimingComponent::Fire()
{
	if (ProjectileClass)
	{
		FVector SpawnLocation = OwnerPawn->GetProjectileSpawnPoint()->GetComponentLocation();
		FRotator SpawnRotation = OwnerPawn->GetProjectileSpawnPoint()->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(OwnerPawn);
	}
}

float UAimingComponent::GetFireRate() const
{
	return FireRate;
}

float UAimingComponent::GetFireRange() const
{
	return FireRange;
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

