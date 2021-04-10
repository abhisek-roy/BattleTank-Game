// Copyright 2021, Abhisek Roy

#define OUT

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	if(!BarrelToSet) return;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* TurretToSet)
{
	if(!TurretToSet) return;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankAimingComponent::AimAt(FVector AimLocation, float ProjectileSpeed)
{
	if(!Barrel) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector AimDirection(0);
	TArray < AActor * > ActorsToIgnore = {Cast<AActor>(Barrel)}; // Not sure of the right usage.
	bool HasValidSol = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		AimLocation,
		ProjectileSpeed,
		false,
		0.0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		// , ECR_Block,
		// ActorsToIgnore,
		// false
		);

	if ( HasValidSol )
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}


void UTankAimingComponent::MoveBarrelTowards( FVector AimDirection )
{
	// Convert AimDirection to Polar Coordinates
	// Get Barrel reference
	
	// Find the differences between current barrel rotation and aimdirection
	if(!Barrel) return;
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	ElevateBarrel(DeltaRotator.Pitch);
	
	if (DeltaRotator.Yaw > 180.f)
	{
		OrientTurret(-1.f);
	}
	else if (DeltaRotator.Yaw < -180.f)
	{
		OrientTurret(1.f);
	}
	else
	{
		OrientTurret(DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::ElevateBarrel(float RelSpeed)
{
	// Move the barrel the right about this frame
	// Given a max elevation speed, and the frame time
    // RelSpeed -1 to +1
	float MaxDegreesPerSec = 5.f;
	float MinElevationDeg = 5.f;
	float MaxElevationDeg = 40.f;

    RelSpeed = FMath::Clamp<float>(RelSpeed, -1, 1);
	float Attitude = Barrel->RelativeRotation.Pitch + RelSpeed * 5.0f * GetWorld()->DeltaTimeSeconds;
    Attitude = FMath::Clamp<float>(Attitude, 0.f, 40.f);
    Barrel->SetRelativeRotation(FRotator(Attitude, 0,0));
}

void UTankAimingComponent::OrientTurret(float RelSpeed)
{
	float MaxDegreesPerSec = 15.f;
	// Move the barrel the right about this frame
	// Given a max elevation speed, and the frame time
    // RelSpeed -1 to +1
    RelSpeed = FMath::Clamp<float>(RelSpeed, -1, 1);
    
    float Yaw = Turret->RelativeRotation.Yaw + RelSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
    Turret->SetRelativeRotation(FRotator(0, Yaw, 0));	
	}