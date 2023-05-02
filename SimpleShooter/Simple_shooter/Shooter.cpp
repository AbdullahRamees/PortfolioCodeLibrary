
#include "Shooter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "Simple_shooterGameModeBase.h"

// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("weapon_Socket"));
	Gun->SetOwner(this);
}

bool AShooter::IsDead() const
{
	if(Health<=0){
		return true;
	}
	return false;
}

float AShooter::GetHealth() const
{
	return Health/MaxHealth;
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooter::MoveForward);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AShooter::Turn);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooter::JumpPlayer);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&AShooter::Shoot);
}

float AShooter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToTake = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	DamageToTake = FMath::Min(Health,DamageToTake);
	Health -= DamageToTake;
	if(IsDead()){
		ASimple_shooterGameModeBase* Gamemode = GetWorld()->GetAuthGameMode<ASimple_shooterGameModeBase>();
		if(Gamemode){
			Gamemode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageToTake;
}

void AShooter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShooter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AShooter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AShooter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AShooter::JumpPlayer()
{
	Super::Jump();
}

void AShooter::Shoot()
{
	Gun->PullTrigger();
}





