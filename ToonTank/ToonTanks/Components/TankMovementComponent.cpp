// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

void UTankMovementComponent::Move(float Direction)
{
	MovementDirection = FVector(Direction * MovementSpeed * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f);

	
	PawnOwner->AddActorLocalOffset(MovementDirection, true);
}

void UTankMovementComponent::RotateBase(float Direction)
{

	float RotateAmount = Direction * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0.0f, RotateAmount, 0.0f);
	RotationDirection = FQuat(Rotation);
	PawnOwner->AddActorLocalRotation(RotationDirection, true);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = PawnOwner->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardDirection = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightDirection = FVector::CrossProduct(TankForward, AIForwardIntention);

	RotateBase(RightDirection.Z);
	Move(ForwardDirection);
}
