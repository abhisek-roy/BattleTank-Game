// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime) override;
private:
	ATank* AITank = nullptr;
	ATank* PlayerPawn = nullptr;
};
