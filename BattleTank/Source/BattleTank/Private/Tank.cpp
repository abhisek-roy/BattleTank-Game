// Copyright 2021, Abhisek Roy

#include "Tank.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// No need to protect component as constructed in the constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UStaticMeshComponent* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Aiming
void ATank::AimAt( FVector AimLocation)
{
	TankAimingComponent->AimAt(AimLocation, ProjectileSpeed);
}

// Firing
void ATank::Fire()
{
	// UE_LOG(LogTemp, Warning, TEXT("Tank is firing"));

	bool IsReloaded = FPlatformTime::Seconds() > ReloadTime + LastFiredAt;
	// if(Barrel && IsReloaded)
	// {
	// 	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
	// 		Barrel->GetSocketLocation(FName("Projectile")), 
	// 		Barrel->GetSocketRotation(FName("Projectile"))
	// 	);

	// 	Projectile->Launch(ProjectileSpeed);
	// 	LastFiredAt = FPlatformTime::Seconds();
	// }
}

void ATank::ApplyForce(float Throttle, UStaticMeshComponent* Track)
{
	if(!Track) return;
	UE_LOG(LogTemp, Warning, TEXT("%s appling %f throttle."), *Track->GetName(), Throttle);

	Throttle = FMath::Clamp(Throttle, -1.f, 1.f);
	auto Force = Track->GetForwardVector() * Throttle * MaxTractiveForce;
	auto Location = Track->GetComponentLocation();

	Track->AddForceAtLocation(Force, Location);
}