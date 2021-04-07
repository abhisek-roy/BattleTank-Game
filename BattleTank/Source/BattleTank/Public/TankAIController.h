// Copyright 2021, Abhisek Roy

#pragma once

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime) override;
private:
	ATank* AITank;
	ATank* PlayerPawn;
	
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
};
