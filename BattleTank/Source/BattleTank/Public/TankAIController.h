// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * Defines the AI Tank behaviour.
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime) override;

	// How close can the AI tank get
	float AcceptanceRadius = 6000;

private:
	ATank* AITank = nullptr;
	ATank* PlayerPawn = nullptr;
};
