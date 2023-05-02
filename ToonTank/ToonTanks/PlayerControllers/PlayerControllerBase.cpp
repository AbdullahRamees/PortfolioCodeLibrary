// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "Blueprint/UserWidget.h"
#include "../Components/TankMovementComponent.h"
#include "../Components/AimingComponent.h"
#include "../Pawns/PawnTank.h"


void APlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Movement Behavior
	PawnMovementComponent->Move(ForwardMovementDirection);
	PawnMovementComponent->RotateBase(RotationMovementDirection);
	//Aiming Behavior
	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
	FVector HitLocation = TraceHitResult.ImpactPoint;
	AimingComponent->RotateTurret(HitLocation);
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
	//Creation of Health Widget
	UUserWidget* HealthWidget = CreateWidget(this, HealthScreenClass);
	if (HealthWidget != nullptr)
	{
		HealthWidget->AddToViewport();
	}

	PlayerTank = Cast<APawnTank>(GetPawn());
	if (PlayerTank)
	{
		PawnMovementComponent = PlayerTank->FindComponentByClass<UTankMovementComponent>();
		AimingComponent = PlayerTank->FindComponentByClass<UAimingComponent>();
	}
}

void APlayerControllerBase::CalculateMoveInput(float Value)
{
	ForwardMovementDirection = Value;
}

void APlayerControllerBase::CalculateRotationInput(float Value)
{
	RotationMovementDirection = Value;
}

void APlayerControllerBase::Fire()
{
	AimingComponent->Fire();
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerControllerBase::CalculateMoveInput);
	InputComponent->BindAxis("Turn", this, &APlayerControllerBase::CalculateRotationInput);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerControllerBase::Fire);

}

void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
	bShowMouseCursor = SetPlayerEnabled;
}