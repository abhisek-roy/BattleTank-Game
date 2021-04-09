// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Orient( float RelSpeed ); // Elevates at a relative speed

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSec = 15.f;
};
