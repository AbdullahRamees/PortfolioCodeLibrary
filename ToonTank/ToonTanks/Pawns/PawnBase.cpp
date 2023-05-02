// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/AimingComponent.h"
#include "../Actors/ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	AimingComponent = CreateDefaultSubobject<UAimingComponent>(TEXT("Aiming Component"));
}

UStaticMeshComponent* APawnBase::GetTurretMesh() const
{
	return TurretMesh;
}

float APawnBase::GetCombatRange() const
{
	return CombatRange;
}

void APawnBase::RegainHealth(float HealthValue)
{
	HealthComponent->RegainHealth(HealthValue);
}

float APawnBase::GetAcceptanceRadius() const
{
	return AcceptanceRadius;
}

void APawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
	Destroy();
}

float APawnBase::GetRemainingHealth() const
{
	return HealthComponent->CalculateHealthPercetage();
}

UAimingComponent* APawnBase::GetAimingComponent() const
{
	return AimingComponent;
}

USceneComponent* APawnBase::GetProjectileSpawnPoint() const
{
	return ProjectileSpawnPoint;
}
