// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * Defines the AI Tank behaviour.
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime) override;

	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", ClampMax = "10000", UIMin = "0.0", UIMax = "10000"))
	float AcceptanceRadius = 6000;

private:
	UTankAimingComponent* AimingComponent;
};
