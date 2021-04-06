// Copyright 2021, Abhisek Roy


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    ATank* AITank = GetControlledTank();

    if(!AITank) return;
    UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing: %s."), *AITank->GetName());
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}