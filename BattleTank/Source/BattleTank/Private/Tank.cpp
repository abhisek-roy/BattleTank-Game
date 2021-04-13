// Copyright 2021, Abhisek Roy

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// Sets up Aiming and Movement components, and passes on Tank properties.
	auto AimingComponent = this->FindComponentByClass<UTankAimingComponent>();
	auto MovementComponent = this->FindComponentByClass<UTankMovementComponent>();

	if( !ensure(AimingComponent)) return;
	if( !ensure(MovementComponent)) return;

	// Passing on Tank properties to the respetive controllers
	MovementComponent->MaxTractiveForce = MaxTractiveForce;
	AimingComponent->ReloadTime = ReloadTime;
	AimingComponent->ProjectileSpeed = ProjectileSpeed;
	AimingComponent->BarrelMaxDegreesPerSec = BarrelMaxDegreesPerSec;
	AimingComponent->MinElevationDeg = MinElevationDeg;
	AimingComponent->MaxElevationDeg = MaxElevationDeg;
	AimingComponent->TurretMaxDegreesPerSec = TurretMaxDegreesPerSec;
}

