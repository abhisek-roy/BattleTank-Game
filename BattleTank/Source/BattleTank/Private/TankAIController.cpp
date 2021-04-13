// Copyright 2021, Abhisek Roy

#include "TankAIController.h"
#include "Tank.h"
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
    if(!ensure(AITank)) return;
    if(!ensure(PlayerPawn)) return;

    // Move towards Player
    MoveToActor(PlayerPawn, AcceptanceRadius);

    // Aim towards Player
    AITank->AimAt(PlayerPawn->GetActorLocation());
    
    // Fire if ready
    AITank->Fire();
}

