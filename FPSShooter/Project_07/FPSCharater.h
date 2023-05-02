// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharater.generated.h"


class UWidgetComponent;
class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class PROJECT_07_API AFPSCharater : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharater();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	//Checking Dead
	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	//Checking Health
	UFUNCTION(BlueprintPure)
		float GetHealth() const;

	//TakeDamaeg Overiding
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	void Shoot();


	float GetMaxFireRange() const;


private:
	//Movement Inputs
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void JumpPlayer();


	//health Propertices
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
		float Health;

	//GunEvents
	//Muzzle Flash
	UPROPERTY(EditAnywhere)
		UParticleSystem* GunFlash;
	//Hit 
	UPROPERTY(EditAnywhere)
		UParticleSystem* HitParticle;

	//shoot sound
	UPROPERTY(EditAnywhere)
		USoundBase* GunSound;

	//HitSound
	UPROPERTY(EditAnywhere)
		USoundBase* HitSound;

	//shoooting properties
	UPROPERTY(EditAnywhere)
		float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
		float Damage = 10.f;


	bool GunLineTrace(FHitResult& HitPoint, FVector& ShotDiraction);

	

	//Debugging
	UPROPERTY(EditAnywhere)
		bool canLog;

};
