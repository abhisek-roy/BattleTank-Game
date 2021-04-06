// Copyright 2021, Abhisek Roy


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    ATank* AITank = GetControlledTank();
    ATank* PlayerPawn = GetPlayerTank();

    if(!AITank) return;
    if(!PlayerPawn) return;

    UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing: %s. Found: %s."), *AITank->GetName(), *PlayerPawn->GetName());
}

ATank* ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}