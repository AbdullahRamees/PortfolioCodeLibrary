// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class ATankGameModeBase;

UCLASS()
class TOONTANKS_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* DoorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Threshold", meta = (AllowPrivateAccess = true))
	int EnemyThreshold;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = true))
	bool IsOpen = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door Positions", meta = (AllowPrivateAccess = true))
	FVector OpenLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door Positions", meta = (AllowPrivateAccess = true))
	FVector ClosedLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door Positions", meta = (AllowPrivateAccess = true))
	float DoorOffset = 80.0f;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* OpenSound;
	int EnemyNumber;
	ATankGameModeBase* CurrentGameMode;
};
