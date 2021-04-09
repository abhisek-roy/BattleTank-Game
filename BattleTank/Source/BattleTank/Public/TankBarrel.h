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
	float MaxDegreesPerSec = 5.f;
	float MinElevationDeg = 5.f;
	float MaxElevationDeg = 40.f;
};
