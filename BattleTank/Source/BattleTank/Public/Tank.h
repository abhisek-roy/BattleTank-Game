// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankAimingComponent;
class UTankMovementComponent;

/**
 * Defines the Tank and its properties
 */
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt( FVector AimLocation);

	UFUNCTION( BlueprintCallable, Category = Setup)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* MovementComponent = nullptr;

private:
	UFUNCTION( BlueprintCallable, Category = Setup)
	void Initialize(UTankAimingComponent* AimingComponentToSet, UTankMovementComponent* MovementComponentToSet);

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxTractiveForce = 30000000.0f;

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
};
