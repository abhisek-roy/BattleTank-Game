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
	Locked,
	OutOfAmmo
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

	EFiringState GetFiringState() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentAmmo;

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

	UPROPERTY(EditDefaultsOnly, Category = Firing, meta = (ClampMin = "0", ClampMax = "300", UIMin = "0", UIMax = "300"))
	int32 TotalAmmo = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing, meta = (ClampMin = "0.0", ClampMax = "10000", UIMin = "0.0", UIMax = "10000"))
	float ProjectileSpeed = 4000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ReloadTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing, meta = (ClampMin = "0.0", ClampMax = "30", UIMin = "0.0", UIMax = "30"))
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
