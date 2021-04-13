// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class AProjectile;

/**
 * Auto-aiming components
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	float ReloadTime;
	float ProjectileSpeed;
	float BarrelMaxDegreesPerSec;
	float MinElevationDeg;
	float MaxElevationDeg;
	float TurretMaxDegreesPerSec;

	void AimAt(FVector AimLocation);
	
	UFUNCTION( BlueprintCallable, Category = "Setup")
	void Initialize(UStaticMeshComponent* BarrelToSet, UStaticMeshComponent* TurretToSet);
	
	UFUNCTION( BlueprintCallable, Category = "Setup")
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringState FiringState = EFiringState::Aiming;

private:
	UStaticMeshComponent* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;


	float LastFiredAt = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;


	void MoveBarrelTowards(FVector AimDirection);
	void ElevateBarrel(float RelSpeed);
	void OrientTurret(float RelSpeed);

};
