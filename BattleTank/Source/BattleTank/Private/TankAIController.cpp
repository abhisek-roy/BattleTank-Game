// Copyright 2021, Abhisek Roy

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    AITank = GetControlledTank();
    PlayerPawn = GetPlayerTank();

    if(!AITank) return;
    if(!PlayerPawn) return;

    UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing: %s. Found: %s."), *AITank->GetName(), *PlayerPawn->GetName());
}

void ATankAIController::Tick( float DeltaTime)
{
    Super::Tick( DeltaTime);

    if(!AITank) return;
    if(!PlayerPawn) return;

    // Move towards Player

    // Aim towards Player
    AITank->AimAt(PlayerPawn->GetActorLocation());
    
    // Fire if ready
}

ATank* ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}