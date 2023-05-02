// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharater.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "KillThemAllGameMode.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AFPSCharater::AFPSCharater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh(),TEXT("head"));
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	//setup healthbar
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetRelativeLocation(FVector(0.f, 0.f, 110.f));

}

// Called when the game starts or when spawned
void AFPSCharater::BeginPlay()
{
	Super::BeginPlay();
	//initiate health
	Health = MaxHealth;
	
}

// Called every frame
void AFPSCharater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//checking dead and hiding health bar
	if (IsDead()) {
		HealthBar->SetHiddenInGame(true);
	}
}

// Called to bind functionality to input
void AFPSCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AFPSCharater::MoveForward);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AFPSCharater::LookUp);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AFPSCharater::Turn);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AFPSCharater::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharater::JumpPlayer);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharater::Shoot);

}

//check dead function
bool AFPSCharater::IsDead() const
{
	if (Health <= 0) {
		return true;
		
	}
	return false;
}

//geting health function
float AFPSCharater::GetHealth() const
{
	return Health;
}

//damage handle
float AFPSCharater::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToTake = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToTake = FMath::Min(Health, DamageToTake);
	Health -= DamageToTake;
	if (IsDead()) {
		AKillThemAllGameMode* Gamemode = GetWorld()->GetAuthGameMode<AKillThemAllGameMode>();
		if (Gamemode) {
			Gamemode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageToTake;
}

//movement functions
void AFPSCharater::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AFPSCharater::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AFPSCharater::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AFPSCharater::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AFPSCharater::JumpPlayer()
{
	Super::Jump();
}

//Gwetter for gun range
float AFPSCharater::GetMaxFireRange() const
{
	return MaxRange;
}

//linetrace for shoot
bool AFPSCharater::GunLineTrace(FHitResult& HitPoint, FVector& ShotDiraction)
{

	AController* OwnerController = GetController();
	FVector ViewpontLocation;
	FRotator ViewpontRotation;
	OwnerController->GetPlayerViewPoint(ViewpontLocation, ViewpontRotation);
	FVector EndPoint = ViewpontLocation + ViewpontRotation.Vector() * MaxRange;
	ShotDiraction = -ViewpontRotation.Vector();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitPoint, ViewpontLocation, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

//shoot function handle Vfx and SFX
void AFPSCharater::Shoot()
{
	UGameplayStatics::SpawnEmitterAttached(GunFlash, GetMesh(), TEXT("Muzzle_01"));
	UGameplayStatics::SpawnSoundAttached(GunSound, GetMesh(), TEXT("Muzzle_01"));

	FHitResult Hit;
	FVector ShotDiraction;
	bool bSuccess = GunLineTrace(Hit, ShotDiraction);
	if (bSuccess) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Hit.Location, ShotDiraction.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, Hit.Location, ShotDiraction.Rotation());
		AActor* HitActor = Hit.GetActor();
		AController* OwnerController = GetController();
		if (OwnerController == nullptr) return;
		if (HitActor != nullptr) {
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDiraction, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
	//DrawDebugCamera(GetWorld(),ViewpontLocation,ViewpontRotation,90,2,FColor::Red,true);
}
