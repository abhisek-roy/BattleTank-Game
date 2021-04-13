// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
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
