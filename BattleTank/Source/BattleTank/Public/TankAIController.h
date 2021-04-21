// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
class ATank;

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
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", ClampMax = "20000", UIMin = "0.0", UIMax = "20000"))
	float AcceptanceRadius = 8000;

private:
	UTankAimingComponent* AimingComponent;
	ATank* PossesedTank = nullptr;

	virtual void SetPawn(APawn* InPawn) override; // Need this to append extra functionality
	
	UFUNCTION()
	void OnPossesedTankDeath();
};
