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

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	void MoveBarrelTowards(FVector AimDirection);
	void ElevateBarrel(float RelSpeed);
	void OrientTurret(float RelSpeed);
	bool IsLocked();

	UStaticMeshComponent* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileSpeed = 4000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float BarrelMaxDegreesPerSec = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float MinElevationDeg = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float MaxElevationDeg = 40.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float TurretMaxDegreesPerSec = 15.f;

	float LastFiredAt = 0.f;
	FVector AimDirection = FVector(0);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;
};
