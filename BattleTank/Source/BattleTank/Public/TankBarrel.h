// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate( float RelSpeed ); // Elevates at a relative speed

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSec = 20.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDeg = -5.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDeg = 30.f;
};
