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

// Sets up Aiming and Movement components, and passes on Tank properties.
void ATank::Initialize(UTankAimingComponent* AimingComponentToSet, UTankMovementComponent* MovementComponentToSet)
{
	if( !AimingComponentToSet || !MovementComponentToSet) return;
	AimingComponent = AimingComponentToSet;
	MovementComponent = MovementComponentToSet;

	// Passing on Tank properties to the respetive controllers
	MovementComponent->MaxTractiveForce = MaxTractiveForce;
	AimingComponent->ReloadTime = ReloadTime;
	AimingComponent->ProjectileSpeed = ProjectileSpeed;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Aiming
void ATank::AimAt( FVector AimLocation)
{
	AimingComponent->AimAt(AimLocation);
}

// Firing
void ATank::Fire()
{
	AimingComponent->Fire();
}

