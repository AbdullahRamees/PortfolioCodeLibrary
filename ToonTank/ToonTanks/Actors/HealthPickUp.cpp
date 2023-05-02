// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "Components/StaticMeshComponent.h"
#include "../Pawns/PawnPlayerTank.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHealthPickUp::AHealthPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthPickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Health PickUp Mesh"));
	HealthPickUpMesh->OnComponentHit.AddDynamic(this, &AHealthPickUp::OnHit);
	RootComponent = HealthPickUpMesh;
}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<APawnPlayerTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, GetWorld()->DeltaTimeSeconds * RotationSpeed, 0.0f));

}

void AHealthPickUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == PlayerTank)
	{
		PlayerTank->RegainHealth(HealthValue);
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		Destroy();
	}
	else
	{
		return;
	}
}

