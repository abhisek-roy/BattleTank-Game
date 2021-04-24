// Copyright 2021, Abhisek Roy

#define OUT

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::Initialize(UStaticMeshComponent* BarrelToSet, UStaticMeshComponent* TurretToSet)
{
    if(!ensure(BarrelToSet && TurretToSet)) return;
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFiredAt = FPlatformTime::Seconds();
	CurrentAmmo = TotalAmmo;

	// TurretSound = CreateDefaultSubobject<UAudioComponent>(FName("Turret Sound"));
	// TurretSound->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	// TurretSound->bAutoActivate = false;

	// ReloadedSound = CreateDefaultSubobject<UAudioComponent>(FName("Reload Sound"));
	// ReloadedSound->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	// ReloadedSound->bAutoActivate = false;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if( CurrentAmmo < 1 )
	{
		FiringState = EFiringState::OutOfAmmo;
		PlayReloadSound = false;
		PlayActuatorSound = false;
	}else if( FPlatformTime::Seconds() < ReloadTime + LastFiredAt)
	{
		FiringState = EFiringState::Reloading;
		PlayReloadSound = false;
	}else if (IsLocked())
	{
		FiringState = EFiringState::Locked;
		// if(!ReloadedSound) return;
		if(!PlayedReloadSound) 
		{
			PlayReloadSound = true;
			PlayedReloadSound = true;
		}else PlayReloadSound = false;
	}else
	{
		FiringState = EFiringState::Aiming;
		// Queue the loading sound to be played after ReloadTime
		if(!PlayedReloadSound) 
		{
			PlayReloadSound = true;
			PlayedReloadSound = true;
		}else PlayReloadSound = false;
	}

	if ( IsBarrelMoving || IsTurretMoving )
	{
		PlayActuatorSound = true;
	}else
	{
		PlayActuatorSound = false;
	}
	IsBarrelMoving = false;
	IsTurretMoving = false;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsLocked()
{
	if (!ensure(Barrel)) return false;

	auto BarrelRotator = Barrel->GetForwardVector();
	return BarrelRotator.Equals( AimDirection , 0.01);
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if(!ensure(Barrel)) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
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
	if(!ensure(Barrel)) return;
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
	if(!ensure(Barrel)) return;

    RelSpeed = FMath::Clamp<float>(RelSpeed, -1, 1);
	float Attitude = Barrel->GetRelativeRotation().Pitch + RelSpeed * BarrelMaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
    Attitude = FMath::Clamp<float>(Attitude, MinElevationDeg, MaxElevationDeg);

	if(FMath::Abs( Attitude - Barrel->GetRelativeRotation().Pitch) > 0.05f)
	{
		IsBarrelMoving = true;
	}else
	{
		IsBarrelMoving = false;
	}

    Barrel->SetRelativeRotation(FRotator(Attitude, 0,0));
}

void UTankAimingComponent::OrientTurret(float RelSpeed)
{
	// Move the turret the right about this frame
	// Given a max rotation speed, and the frame time
    // RelSpeed -1 to +1
	if(!ensure(Turret)) return;
    RelSpeed = FMath::Clamp<float>(RelSpeed, -1, 1);
    
    float Yaw = Turret->GetRelativeRotation().Yaw + RelSpeed * TurretMaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
    Turret->SetRelativeRotation(FRotator(0, Yaw, 0));

	if(FMath::Abs(RelSpeed * TurretMaxDegreesPerSec) > 1.f)
	{
		IsTurretMoving = true;
	}else
	{
		IsTurretMoving = false;
	}	
}

// Firing
void UTankAimingComponent::Fire()
{
	if(!ProjectileBlueprint) UE_LOG(LogTemp, Error, TEXT("Projectile BLueprint not set.")); 

	if(ensure(Barrel) && ensure(ProjectileBlueprint) && FiringState != EFiringState::Reloading && CurrentAmmo > 0)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
			Barrel->GetSocketLocation(FName("Projectile")), 
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->Launch(ProjectileSpeed);
		LastFiredAt = FPlatformTime::Seconds();
		CurrentAmmo--;
		PlayedReloadSound = false;
	}
}

bool UTankAimingComponent::bPlayActuatorSound()
{
	return PlayActuatorSound;
}

bool UTankAimingComponent::bPlayReloadSound()
{
	return PlayReloadSound;
}
