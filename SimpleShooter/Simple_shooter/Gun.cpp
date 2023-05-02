// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{	
	UGameplayStatics::SpawnEmitterAttached(GunFlash,Mesh,TEXT("Muzzle_01"));
	UGameplayStatics::SpawnSoundAttached(GunSound,Mesh,TEXT("Muzzle_01"));

	FHitResult Hit;
	FVector ShotDiraction;
	bool bSuccess = GunLineTrace(Hit,ShotDiraction);
	if(bSuccess){
		//DrawDebugPoint(GetWorld(),HitPoint.Location,20,FColor::Red,true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticle,Hit.Location,ShotDiraction.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),HitSound,Hit.Location,ShotDiraction.Rotation());
		AActor* HitActor = Hit.GetActor();
		AController* OwnerController = GetOwnerController();
				if(OwnerController == nullptr) return;
		if(HitActor != nullptr){
			FPointDamageEvent DamageEvent(Damage,Hit,ShotDiraction,nullptr);
			HitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}
	}
	//DrawDebugCamera(GetWorld(),ViewpontLocation,ViewpontRotation,90,2,FColor::Red,true);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AGun::GetMaxFireRange() const
{
	return MaxRange;
}

bool AGun::GunLineTrace(FHitResult& HitPoint,FVector& ShotDiraction)
{
	AController* OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return false;
	FVector ViewpontLocation;
	FRotator ViewpontRotation;
	OwnerController->GetPlayerViewPoint(ViewpontLocation,ViewpontRotation);
	FVector EndPoint  =ViewpontLocation + ViewpontRotation.Vector()* MaxRange;
	ShotDiraction = -ViewpontRotation.Vector();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitPoint,ViewpontLocation,EndPoint,ECollisionChannel::ECC_GameTraceChannel1,Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
}





