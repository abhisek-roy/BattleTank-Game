// Copyright 2021, Abhisek Roy

#include "Tank.h"
#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime)
{
    Super::Tick( DeltaTime);

    AITank = Cast<ATank>(GetPawn());
    PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if(!AITank) return;
    if(!PlayerPawn) return;

    // Move towards Player

    // Aim towards Player
    AITank->AimAt(PlayerPawn->GetActorLocation());
    
    // Fire if ready
    AITank->Fire();
}

