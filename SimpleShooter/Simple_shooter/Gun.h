// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLE_SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetMaxFireRange() const;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* GunFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere)
	USoundBase* GunSound;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f; 

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	bool GunLineTrace(FHitResult& HitPoint,FVector& ShotDiraction);

	AController* GetOwnerController() const;
};
