// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameActor.h"
#include "Components/BoxComponent.h"
#include "KillThemAllGameMode.h"

// Sets default values
AEndGameActor::AEndGameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setup Box trigger
	EndBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EndBox"));
	EndBox->SetupAttachment(RootComponent);
	EndBox->SetGenerateOverlapEvents(true);
	EndBox->OnComponentBeginOverlap.AddDynamic(this, &AEndGameActor::OnOverlap);
}

// Called when the game starts or when spawned
void AEndGameActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndGameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//overlap function
void AEndGameActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AKillThemAllGameMode* Gamemode = GetWorld()->GetAuthGameMode<AKillThemAllGameMode>();
	if (Gamemode) {
		Gamemode->EndGame(true);
	}
	
}



