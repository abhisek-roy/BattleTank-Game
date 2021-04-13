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

void ATank::Initialize(UTankAimingComponent* AimingComponentToSet, UTankMovementComponent* MovementComponentToSet)
{
	if( !ensure(AimingComponentToSet && MovementComponentToSet ) ) return;
    AimingComponent = AimingComponentToSet;
    MovementComponent = MovementComponentToSet;

    // Passing on Tank properties to the respetive controllers
    MovementComponent->MaxTractiveForce = MaxTractiveForce;
    AimingComponent->ReloadTime = ReloadTime;
    AimingComponent->ProjectileSpeed = ProjectileSpeed;
	AimingComponent->BarrelMaxDegreesPerSec = BarrelMaxDegreesPerSec;
	AimingComponent->MinElevationDeg = MinElevationDeg;
	AimingComponent->MaxElevationDeg = MaxElevationDeg;
	AimingComponent->TurretMaxDegreesPerSec = TurretMaxDegreesPerSec;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// // Sets up Aiming and Movement components, and passes on Tank properties.
	auto AimingComponent = this->FindComponentByClass<UTankAimingComponent>();
	auto MovementComponent = this->FindComponentByClass<UTankMovementComponent>();

	if( !ensure(AimingComponent)) UE_LOG(LogTemp, Warning, TEXT("Aiming Comp not found"));
	if( !ensure(MovementComponent)) UE_LOG(LogTemp, Warning, TEXT("Move Comp not found"));

	if( !ensure(AimingComponent && MovementComponent)) return;

	// Passing on Tank properties to the respetive controllers
	MovementComponent->MaxTractiveForce = MaxTractiveForce;
	AimingComponent->ReloadTime = ReloadTime;
	AimingComponent->ProjectileSpeed = ProjectileSpeed;
	AimingComponent->BarrelMaxDegreesPerSec = BarrelMaxDegreesPerSec;
	AimingComponent->MinElevationDeg = MinElevationDeg;
	AimingComponent->MaxElevationDeg = MaxElevationDeg;
	AimingComponent->TurretMaxDegreesPerSec = TurretMaxDegreesPerSec;
}

// Aiming
void ATank::AimAt( FVector AimLocation)
{
	if(!ensure(AimingComponent)) return;
	AimingComponent->AimAt(AimLocation);
}

// Firing
void ATank::Fire()
{
	if(!ensure(AimingComponent)) return;
	AimingComponent->Fire();
}

